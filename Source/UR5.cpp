#include "../Header/UR5.h"
#include <wx/wx.h>

UR5::UR5()
{
    ur5 = modbus_new_tcp("192.168.100.11", 502);
    if (modbus_connect(ur5) == -1)
    {
        wxLogMessage("Modbus: Connection Failed!");
    }
    else
    {
        connected = true;
    }
}
UR5::~UR5()
{
    modbus_free(ur5);
}

void UR5::setX(uint16_t cellX)
{
    uint16_t val = xCorner + 40 * cellX;
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set x!");
    }
    else
    {
        wxLogMessage("Set x=%d", val);
        modbus_write_register(ur5, 128, val);
    }
}

void UR5::setY(uint16_t cellY)
{
    uint16_t val = yCorner + 40 * cellY;
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set y!");
    }
    else
    {
        wxLogMessage("Set y=%d", val);
        modbus_write_register(ur5, 129, val);
    }
}

void UR5::setZ(uint16_t val)
{
    if (!isConnected())
    {
        wxLogMessage("Modbus: Counldn't set z!");
    }
    else
    {
        wxLogMessage("Set z=%d", val);
        modbus_write_register(ur5, 130, val);
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
        wxLogMessage("Set DO=%d", val);
        modbus_write_register(ur5, 1, val);
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
        modbus_read_registers(ur5, 1, 1, &val);
        wxLogMessage("Get DO=%d", val);
        return val;
    }
}

bool UR5::isConnected()
{
    return connected;
}
