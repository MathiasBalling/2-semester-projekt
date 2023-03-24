#include "../Header/UR5.h"

UR5::UR5()
{
    mb = modbus_new_tcp("192.168.100.11", 502);
    if (modbus_connect(mb) == -1)
    {
        wxLogMessage("Modbus: Connection Failed!");
    }
    else
    {
        wxLogMessage("Modbus: Connection Successful!");
        connected = true;
        _member_thread = std::thread(&UR5::movePiece, this);
    }
}

uint16_t UR5::getX(int cellX)
{

    uint16_t val = xCorner + 40 * cellX;
    return val;
}

uint16_t UR5::getY(int cellY)
{
    uint16_t val = yCorner + 1 / 8 * dX * cellY;
    return val;
}

void UR5::setXval(uint16_t val)
{
    int msg = modbus_write_register(mb, 128, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set x!");
    }
}

void UR5::setYval(uint16_t val)
{
    int msg = modbus_write_register(mb, 129, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set y!");
    }
}

void UR5::setZval(uint16_t val)
{
    int msg = modbus_write_register(mb, 130, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set z!");
    }
}

void UR5::setCO(uint16_t val)
{
    int msg = modbus_write_register(mb, 31, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set Digital Output!");
    }
}

int UR5::getDO()
{
    uint16_t val;
    int msg = modbus_read_registers(mb, 1, 1, &val);
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

bool UR5::isConnected()
{
    return connected;
}

void UR5::movePiece()
{
    using namespace std::chrono_literals;
    using namespace std::this_thread;
    getDirection();
    while (isConnected())
    {
        if (shouldRun())
        {
            modbus_connect(mb);
            printQueue();
            // Get piece position from queue
            int x = piecePosQueue[0];
            int y = piecePosQueue[1];
            uint16_t z = piecePosQueue[2];
            // Remove piece position from queue
            piecePosQueue.erase(piecePosQueue.begin(), piecePosQueue.begin() + 3);
            wxLogMessage("Moving to: x=%d y:%d z:%d", x, y, z);

            // Load modbus with coordinates
            setXval(getX(x));
            setYval(getY(y));
            setZval(z);
            sleep_for(100ms);
            setCO(1);            // Start loading UR5 with coordinates and move to piece
            while (getDO() != 2) // Wait for UR5 to reach piece
            {
                sleep_for(200ms);
                if (getDO() == -1)
                {
                    wxLogMessage("Modbus: Error getting Digital Output");
                    break;
                }
            }
            sleep_for(3s); // Wait for grpper to close/open
            setCO(1);
        }
        else
        {
            wxLogMessage("Nothing to move, the queue is empty");
            sleep_for(5s);
        }
    }
}

bool UR5::shouldRun()
{
    // Check if queue has at least 3 elements (x, y, z)
    if (piecePosQueue.size() < 3)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void UR5::moveQueue(int cellX, int cellY, uint16_t z)
{
    // Add piece position to queue
    piecePosQueue.push_back(cellX);
    piecePosQueue.push_back(cellY);
    piecePosQueue.push_back(z);
}

void UR5::printQueue()
{
    if (piecePosQueue.empty())
    {
        wxLogMessage("Queue is empty");
        return;
    }
    for (int i = 0, pos = 0; i <= piecePosQueue.size() - 3; i += 3, pos++)
    {
        wxLogMessage("Pos:%d x:%d y:%d z:%d", pos, piecePosQueue[i], piecePosQueue[i + 1], piecePosQueue[i + 2]);
    }
}

void UR5::getDirection()
{
    uint16_t val[4];
    int msg = modbus_read_registers(mb, 131, 4, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't get starting postition!");
        return;
    }
    else
    {
        uint16_t xCornerBR = val[0];
        uint16_t yCornerBR = val[1];
        uint16_t xCornerTL = val[2];
        uint16_t yCornerTL = val[3];
        xCorner = xCornerBR;
        yCorner = yCornerBR;
        dX = xCornerBR - xCornerTL;
        dY = yCornerBR - yCornerTL;
        wxLogMessage("xCorner: %d yCorner: %d dX: %d dY: %d", xCorner, yCorner, dX, dY);
    }
}