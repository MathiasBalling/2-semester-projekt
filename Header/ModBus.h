#pragma once

// Header Files
#include <modbus.h>

// Standard Libraries
#include <vector>
#include <thread>
#include <chrono>

// wxWidgets
#include <wx/wx.h>

class ModBus
{
private:
    int _xCorner = 0, _yCorner = 300;
    int _dX = 320, _dY = 320;
    bool _connected = false;
    std::vector<int> _piecePosQueue;
    std::thread _member_thread;
    modbus_t *_mb;

public:
    ModBus();
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