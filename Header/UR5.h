#pragma once
#include <modbus.h>
#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

class UR5
{
private:
    modbus_t *ur5 = modbus_new_tcp("192.168.100.11", 502);
    uint16_t xCorner = 300;
    uint16_t yCorner = 400;
    bool connected = false;

public:
    UR5();
    void setX(int cellY);
    void setY(int cellY);
    void setZ(int val);
    void setDO(uint16_t val);
    int getDO();
    bool isConnected();
    void movePiece(int x, int y, int z);
};
