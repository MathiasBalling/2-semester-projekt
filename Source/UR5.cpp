#include "../Header/UR5.h"
#include <wx/wx.h>

UR5::UR5()
{
    if (modbus_connect(ur5) == -1)
    {
        wxLogMessage("Modbus: Connection Failed!");
    }
    else
    {
        wxLogMessage("Modbus: Connection Successful!");
        connected = true;
    }
}

void UR5::setX(int cellX)
{
    uint16_t val = xCorner + 40 * cellX;
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set x!");
    }
    else
    {
        int msg = modbus_write_register(ur5, 128, val);
        if (msg == -1)
        {
            wxLogMessage("Modbus: Counldn't set x!");
        }
        else
        {
            wxLogMessage("Set x=%d", val);
        }
    }
}

void UR5::setY(int cellY)
{
    uint16_t val = yCorner + 40 * cellY;
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set y!");
    }
    else
    {
        int msg = modbus_write_register(ur5, 129, val);
        if (msg == -1)
        {
            wxLogMessage("Modbus: Counldn't set y!");
        }
        else
        {
            wxLogMessage("Set y=%d", val);
        }
    }
}

void UR5::setZ(int val)
{
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set z!");
    }
    else
    {
        int msg = modbus_write_register(ur5, 130, val);
        if (msg == -1)
        {
            wxLogMessage("Modbus: Counldn't set z!");
        }
        else
        {
            wxLogMessage("Set z=%d", val);
        }
    }
}

void UR5::setDO(uint16_t val)
{
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set Digital Output!");
    }
    else
    {
        int msg = modbus_write_register(ur5, 1, val);
        if (msg == -1)
        {
            wxLogMessage("Modbus: Counldn't set Digital Output!");
        }
        else
        {
            wxLogMessage("Set DO=%d", val);
        }
    }
}

int UR5::getDO()
{
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't get Digital Output!");
        return -1;
    }
    else
    {
        uint16_t val;
        int msg = modbus_read_registers(ur5, 1, 1, &val);
        if (msg == -1)
        {
            wxLogMessage("Modbus: Counldn't get Digital Output!");
            return -1;
        }
        else
        {
            wxLogMessage("Get DO=%d", val);
            return val;
        }
    }
}

bool UR5::isConnected()
{
    return connected;
}

void UR5::movePiece(int x, int y, int z)
{
    setX(x);
    setY(y);
    setZ(z);
    setDO(1);
    sleep_for(500ms);
    while (getDO() != 3)
    {
        sleep_for(500ms);
    }
    // Insert gripper open/close
    sleep_for(5s);

    setDO(0);
}