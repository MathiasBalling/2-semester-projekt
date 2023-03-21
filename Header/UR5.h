#pragma once
#include <modbus.h>

class UR5
{
private:
    uint16_t xCorner = 50;
    uint16_t yCorner = 350;
    bool connected = false;

public:
    modbus_t *mb;
    UR5();
    void setX(int cellY);
    void setY(int cellY);
    void setZ(int val);
    void setCO(uint16_t val);
    int getDO();
    bool isConnected();
    void movePiece(int x, int y, int z);
};