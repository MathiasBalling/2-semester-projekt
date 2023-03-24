#pragma once
#include <modbus.h>
#include <vector>
#include <thread>
#include <chrono>
#include <wx/wx.h>

class UR5
{
private:
    uint16_t xCorner = 0;
    uint16_t yCorner = 300;
    float dX = 320, dY = 320;
    bool connected = false;
    std::vector<int> piecePosQueue;
    std::thread _member_thread;

public:
    modbus_t *mb;
    UR5();
    uint16_t getX(int cellY);
    uint16_t getY(int cellY);
    void setXval(uint16_t val);
    void setYval(uint16_t val);
    void setZval(uint16_t val);
    void setCO(uint16_t val);
    int getDO();
    bool isConnected();
    void movePiece();
    bool shouldRun();
    void moveQueue(int cellX, int cellY, uint16_t z);
    void printQueue();
    void getDirection();
};