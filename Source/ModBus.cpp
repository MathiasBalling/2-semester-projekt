// Header Files
#include "../Header/ModBus.h"

ModBus::ModBus()
{

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
        // Start a worker thread to move pieces from the queue
        m_thread = std::thread(&ModBus::movePiece, this);

        // Create a new window to display the queue
        m_queueWindow = new QueueWindow(wxT("Queue"));
        m_queueWindow->SetClientSize(wxSize(500, 700));
        m_queueWindow->SetPosition(wxPoint(0, 25));
        m_queueWindow->Show(true);
    }
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
}

uint16_t ModBus::getX(int cellX)
{
    // Calculate the x position of the piece
    int val = m_xCorner - (m_dY * cellX) / 8;

    // The modbus device can't handle negative values
    // Therefore all negative values are converted to positive values and added to 2000
    // e.g. -100 -> 100 + 2000 = 2100 and the robot considers 2100 as -100
    if (val < 0)
    {
        return val = val * -1 + 2000;
    }
    else
    {
        return val;
    }
}

int ModBus::getX(int cellX, bool test)
{
    // Calculate the x position of the piece
    int val = m_xCorner - (m_dY * cellX) / 8;
    return val;
}

uint16_t ModBus::getY(int cellY)
{
    // Calculate the y position of the piece
    int val = m_yCorner - (m_dX * cellY) / 8;

    // The modbus device can't handle negative values
    // Therefore all negative values are converted to positive values and added to 2000
    // e.g. -100 -> 100 + 2000 = 2100 and the robot considers 2100 as -100
    if (val < 0)
    {
        return val = val * -1 + 2000;
    }
    else
    {
        return val;
    }
}

int ModBus::getY(int cellY, bool test)
{
    // Calculate the y position of the piece
    int val = m_yCorner - (m_dX * cellY) / 8;
    return val;
}

void ModBus::setXval(uint16_t val)
{
    // Write the x position to the modbus device
    int msg = modbus_write_register(m_mb, 128, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set x!");
    }
}

void ModBus::setYval(uint16_t val)
{
    // Write the y position to the modbus device
    int msg = modbus_write_register(m_mb, 129, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set y!");
    }
}

void ModBus::setZval(uint16_t val)
{
    // Write the z position to the modbus device
    int msg = modbus_write_register(m_mb, 130, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set z!");
    }
}

void ModBus::setCO(uint16_t val)
{
    // Write the configurable output to the modbus device
    int msg = modbus_write_register(m_mb, 31, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set Digital Output!");
    }
}

int ModBus::getDO()
{
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
            printQueue();
            // Get piece position from queue
            int x = m_piecePosQueue[0];
            int y = m_piecePosQueue[1];
            uint16_t z = m_piecePosQueue[2];

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
    m_queueWindow->addItem(id, operation, getX(cellX, 1), getY(cellY, 1), z);
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

void ModBus::getDirection()
{
    uint16_t val[4];
    int msg = modbus_read_registers(m_mb, 131, 4, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't get starting postition!");
        return;
    }
    else
    {
        int xCornerBR, yCornerBR, xCornerBL, yCornerBL;

        // Convert the values to the correct format
        if (val[0] > 2000)
        {
            xCornerBR = val[0] * -1 + 2000;
        }
        else
        {
            xCornerBR = val[0];
        }

        if (val[1] > 2000)
        {
            yCornerBR = val[1] * -1 + 2000;
        }
        else
        {
            yCornerBR = val[1];
        }

        if (val[2] > 2000)
        {
            xCornerBL = val[2] * -1 + 2000;
        }
        else
        {
            xCornerBL = val[2];
        }

        if (val[3] > 2000)
        {
            yCornerBL = val[3] * -1 + 2000;
        }
        else
        {
            yCornerBL = val[3];
        }

        // Set the values of the corners matching cell(0,0)
        m_xCorner = xCornerBR;
        m_yCorner = yCornerBR;

        // Calculate the difference between the corners
        m_dX = xCornerBL - xCornerBR;
        m_dY = yCornerBR - yCornerBL;
        wxLogMessage("xCorner: %d yCorner: %d dX: %d dY: %d", m_xCorner, m_yCorner, m_dX, m_dY);
    }
}
