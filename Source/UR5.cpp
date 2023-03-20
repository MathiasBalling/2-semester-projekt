#include "../Header/UR5.h"
#include <wx/wx.h>

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
    }
}

UR5::~UR5()
{
    modbus_close(mb);
    modbus_free(mb);
}

void UR5::setX(int cellX)
{
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set x!");
    }
    else
    {
        uint16_t val = xCorner + 40 * cellX;
        int msg = modbus_write_register(mb, 128, val);
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
    int msg = modbus_write_register(mb, 129, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set y!");
    }
    else
    {
        wxLogMessage("Set y=%d", val);
    }
}

void UR5::setZ(int val)
{

    int msg = modbus_write_register(mb, 130, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set z!");
    }
    else
    {
        wxLogMessage("Set z=%d", val);
    }
}

void UR5::setDO(uint16_t val)
{
    mb = modbus_new_tcp("192.168.100.11", 502);
    int msg = modbus_write_register(mb, 1, val);
    if (msg == -1)
    {
        wxLogMessage("Modbus: Counldn't set Digital Output!");
    }
    else
    {
        wxLogMessage("Set DO=%d", val);
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
        wxLogMessage("Get DO=%d", val);
        return val;
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
    wxMilliSleep(500);
    while (getDO() != 3)
    {
    }
    wxMilliSleep(5000); // Wait for piece to be picked up
    setDO(0);
    wxMilliSleep(1000);
}