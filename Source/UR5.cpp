#include "../Header/UR5.h"
#include <wx/wx.h>

UR5::UR5()
{
    ur5 = modbus_new_tcp("192.168.100.11", 502);
    if (modbus_connect(ur5) == -1)
    {
        // fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        wxLogMessage("Modbus: Connection Failed!");
        modbus_free(ur5);
    }
}
UR5::~UR5()
{
    delete this;
}

void UR5::setX(uint16_t cellX)
{
    // xcoord = rand() % (277 - 35 + 1) + 35;
    uint16_t val = xCorner + 40 * cellX;
    wxLogMessage("Set x=%d", val);
    // modbus_write_register(ur5, 128, val);
}

void UR5::setY(uint16_t cellY)
{
    uint16_t val = yCorner + 40 * cellY;
    wxLogMessage("Set y=%d", val);
    // ycoord = rand() % (600 - 400 + 1) + 400;
    // modbus_write_register(ur5, 129, val);
}

void UR5::setZ(uint16_t val)
{
    // zcoord = 200;
    // modbus_write_register(ur5, 130, val);
}

void UR5::setDO(uint16_t val)
{
    modbus_write_register(ur5, 1, val);
}
