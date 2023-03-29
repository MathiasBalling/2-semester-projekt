// Header Files
#include "../Header/ModBus.h"

ModBus::ModBus()
{
    getDirection();

    // Add the ip address of the modbus device
    m_mb = modbus_new_tcp("192.168.100.11", 502);

    // Connect to the modbus device
    if (modbus_connect(m_mb) == -1)
    {
        wxLogMessage("Modbus: Connection Failed!");
    }
    else
    {
        wxLogMessage("Modbus: Connection Successful!");
        m_connected = true;

        // Create a new window to display the queue

        // Start a worker thread to move pieces from the queue
        m_thread = std::thread(&ModBus::movePiece, this);
    }
    int w, h;
    wxDisplaySize(&w, &h);
    w = w - (h - 38 - 30);
    h = (h - 38) / 2;
    m_queueWindow = new QueueWindow(wxT("Move Queue"));
    m_queueWindow->SetSize(wxSize(w, h));
    m_queueWindow->SetPosition(wxPoint(0, 38));
    m_queueWindow->Show(true);

    m_deadPieceWindow = new DeadPieceWindow(wxT("Dead Pieces"));
    m_deadPieceWindow->SetSize(wxSize(w, h));
    m_deadPieceWindow->SetPosition(wxPoint(0, h + 38));
    m_deadPieceWindow->Show(true);
}

ModBus::~ModBus()
{
    // Disconnect from the modbus device
    modbus_close(m_mb);
    modbus_free(m_mb);

    // Stop the worker thread
    m_connected = false;

    // Close the queue window
    delete m_queueWindow;
    delete m_deadPieceWindow;
}

int ModBus::getX(int cellX)
{
    // Calculate the x position of the piece
    int val = m_xCorner + (m_dY * cellX);
    return val;
}

int ModBus::getY(int cellY)
{
    // Calculate the y position of the piece
    int val = m_yCorner - (m_dX * cellY);
    return val;
}

void ModBus::setXval(int val)
{
    if (val < 0)
    {
        val = val * -1 + 2000;
    }
    modbus_connect(m_mb);
    // Write the x position to the modbus device
    int msg = modbus_write_register(m_mb, 128, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set x!");
    }
}

void ModBus::setYval(int val)
{
    if (val < 0)
    {
        val = val * -1 + 2000;
    }
    modbus_connect(m_mb);
    // Write the y position to the modbus device
    int msg = modbus_write_register(m_mb, 129, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set y!");
    }
}

void ModBus::setZval(int val)
{
    if (val < 0)
    {
        val = val * -1 + 2000;
    }
    modbus_connect(m_mb);
    // Write the z position to the modbus device
    int msg = modbus_write_register(m_mb, 130, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set z!");
    }
}

void ModBus::setCO(uint16_t val)
{
    modbus_connect(m_mb);
    // Write the configurable output to the modbus device
    int msg = modbus_write_register(m_mb, 31, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set Digital Output!");
    }
}

int ModBus::getDO()
{
    modbus_connect(m_mb);
    // Read the digital output from the modbus device
    uint16_t val;
    int msg = modbus_read_registers(m_mb, 1, 1, &val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't get Digital Output!");
        return -1;
    }
    else
    {
        return val;
    }
}

bool ModBus::isConnected()
{
    return m_connected;
}

void ModBus::movePiece()
{
    // To stop the thread for a specific amount of time
    using namespace std::chrono_literals;
    using namespace std::this_thread;

    modbus_connect(m_mb);
    while (1)
    {
        if (shouldRun())
        {
            // Get piece position from queue
            int x = m_piecePosQueue[0];
            int y = m_piecePosQueue[1];
            int z = m_piecePosQueue[2];

            // Remove piece position from queue
            m_piecePosQueue.erase(m_piecePosQueue.begin(), m_piecePosQueue.begin() + 3);

            // Remove piece from queue window
            m_queueWindow->removeFirstItem();

            wxLogMessage("Moving to: x=%d y:%d z:%d", x, y, z);

            // Load modbus with coordinates
            setXval(getX(x));
            setYval(getY(y));
            setZval(z);
            sleep_for(100ms);
            setCO(1);            // Tells the UR5 to load the coordinates and move
            while (getDO() != 2) // Wait for UR5 to move
            {
                sleep_for(200ms);
                if (getDO() == -1)
                {
                    wxLogMessage("Modbus: Error getting Digital Output");
                    break;
                }
            }
            sleep_for(3s); // Wait for grpper to close/open
            setCO(1);      // Tells the UR5 continue
        }
        else
        {
            wxLogMessage("Nothing to move, the queue is empty");
            // If the queue is empty, wait 5 seconds and check again
            sleep_for(5s);
        }
    }
}

bool ModBus::shouldRun()
{
    // Check if queue has at least 3 elements (x, y, z)
    if (m_piecePosQueue.size() < 3)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ModBus::moveQueue(const int &cellX, const int &cellY, uint16_t z, const wxString &operation, const wxString &id)
{
    // Add piece position to queue
    m_piecePosQueue.push_back(cellX);
    m_piecePosQueue.push_back(cellY);
    m_piecePosQueue.push_back(z);

    // Add piece position to queue window
    m_queueWindow->addItem(id, operation, getX(cellX), getY(cellY), z);

    if (operation == "To Outside Board")
    {
        setDeadPiece(cellX, cellY, id);
    }
}

void ModBus::printQueue()
{
    if (m_piecePosQueue.empty())
    {
        wxLogMessage("Queue is empty");
        return;
    }
    for (int i = 0, pos = 0; i <= m_piecePosQueue.size() - 3; i += 3, pos++)
    {
        wxLogMessage("Pos:%d x:%d y:%d z:%d", pos, m_piecePosQueue[i], m_piecePosQueue[i + 1], m_piecePosQueue[i + 2]);
    }
}

void ModBus::getDirection(int xCornerBR, int yCornerBR, int xCornerBL, int yCornerBL)
{
    // Set the values of the corners matching cell(0,0)
    m_xCorner = xCornerBR;
    m_yCorner = yCornerBR;

    // Calculate the difference between the corners
    m_dX = (xCornerBL - xCornerBR) / 8;
    m_dY = (yCornerBR - yCornerBL) / 8;
    wxLogMessage("xCorner: %d yCorner: %d dX: %d dY: %d", m_xCorner, m_yCorner, m_dX, m_dY);
}

void ModBus::getDirection()
{
    m_dX = 40;
    m_dY = 40;
    m_yCorner = -300;
    m_xCorner = 0;
}

void ModBus::setDeadPiece(const int &cellX, const int &cellY, const wxString &id)
{
    if (id.find("B_") != -1)
        m_deadPieceWindow->addBlack(id, getX(cellX), getY(cellY));
    else if (id.find("W_") != -1)
        m_deadPieceWindow->addWhite(id, getX(cellX), getY(cellY));
    else
        wxLogMessage("Error: Piece ID not recognized");
}
