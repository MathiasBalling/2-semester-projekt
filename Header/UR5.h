#pragma once
#include <modbus.h>

class UR5
{
private:
    modbus_t *ur5;
    uint16_t xCorner = 300;
    uint16_t yCorner = 400;
    bool connected = false;

public:
    UR5();
    ~UR5();
    void setX(uint16_t cellY);
    void setY(uint16_t cellY);
    void setZ(uint16_t val);
    void setDO(uint16_t val);
    int getDO();
    bool isConnected();
};
