// Header Files
#include "../Header/ModBus.h"

ModBus::ModBus()
{
    _mb = modbus_new_tcp("192.168.100.11", 502);
    if (modbus_connect(_mb) == -1)
    {
        wxLogMessage("Modbus: Connection Failed!");
    }
    else
    {
        wxLogMessage("Modbus: Connection Successful!");
        _connected = true;
        _member_thread = std::thread(&ModBus::movePiece, this);
    }
}

uint16_t ModBus::getX(int cellX)
{

    uint16_t val = _xCorner - 1 / 8 * _dY * cellX;
    return val;
}

uint16_t ModBus::getY(int cellY)
{
    uint16_t val = _yCorner - 1 / 8 * _dX * cellY;
    return val;
}

void ModBus::setXval(uint16_t val)
{
    int msg = modbus_write_register(_mb, 128, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set x!");
    }
}

void ModBus::setYval(uint16_t val)
{
    int msg = modbus_write_register(_mb, 129, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set y!");
    }
}

void ModBus::setZval(uint16_t val)
{
    int msg = modbus_write_register(_mb, 130, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set z!");
    }
}

void ModBus::setCO(uint16_t val)
{
    int msg = modbus_write_register(_mb, 31, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set Digital Output!");
    }
}

int ModBus::getDO()
{
    uint16_t val;
    int msg = modbus_read_registers(_mb, 1, 1, &val);
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
    return _connected;
}

void ModBus::movePiece()
{
    using namespace std::chrono_literals;
    using namespace std::this_thread;
    getDirection();
    while (isConnected())
    {
        if (shouldRun())
        {
            modbus_connect(_mb);
            printQueue();
            // Get piece position from queue
            int x = _piecePosQueue[0];
            int y = _piecePosQueue[1];
            uint16_t z = _piecePosQueue[2];
            // Remove piece position from queue
            _piecePosQueue.erase(_piecePosQueue.begin(), _piecePosQueue.begin() + 3);
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

bool ModBus::shouldRun()
{
    // Check if queue has at least 3 elements (x, y, z)
    if (_piecePosQueue.size() < 3)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void ModBus::moveQueue(int cellX, int cellY, uint16_t z)
{
    // Add piece position to queue
    _piecePosQueue.push_back(cellX);
    _piecePosQueue.push_back(cellY);
    _piecePosQueue.push_back(z);
}

void ModBus::printQueue()
{
    if (_piecePosQueue.empty())
    {
        wxLogMessage("Queue is empty");
        return;
    }
    for (int i = 0, pos = 0; i <= _piecePosQueue.size() - 3; i += 3, pos++)
    {
        wxLogMessage("Pos:%d x:%d y:%d z:%d", pos, _piecePosQueue[i], _piecePosQueue[i + 1], _piecePosQueue[i + 2]);
    }
}

void ModBus::getDirection()
{
    uint16_t val[4];
    int msg = modbus_read_registers(_mb, 131, 4, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't get starting postition!");
        return;
    }
    else
    {
        int xCornerBR, yCornerBR, xCornerBL, yCornerBL;
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

        _xCorner = xCornerBR;
        _yCorner = yCornerBR;
        _dX = xCornerBL - xCornerBR;
        _dY = yCornerBR - yCornerBL;
        wxLogMessage("xCorner: %d yCorner: %d dX: %d dY: %d", _xCorner, _yCorner, _dX, _dY);
    }
}