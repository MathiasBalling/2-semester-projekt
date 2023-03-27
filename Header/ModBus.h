#pragma once

// Header Files
#include "../Header/QueueWindow.h"

// Standard Libraries
#include <vector>
#include <thread>
#include <chrono>

// wxWidgets
#include <wx/wx.h>

// Modbus
#include <modbus.h>

class ModBus
{
private:
    int m_xCorner = 0, m_yCorner = -300;
    int m_dX = 320, m_dY = 320;
    bool m_connected = false;
    std::vector<int> m_piecePosQueue;
    std::thread m_thread;
    modbus_t *m_mb;
    QueueWindow *m_queueWindow;

public:
    ModBus();
    ~ModBus();
    uint16_t getX(int cellY);
    uint16_t getY(int cellY);
    int getX(int cellY, bool test);
    int getY(int cellY, bool test);
    void setXval(uint16_t val);
    void setYval(uint16_t val);
    void setZval(uint16_t val);
    void setCO(uint16_t val);
    int getDO();
    bool isConnected();
    void movePiece();
    bool shouldRun();
    void moveQueue(const int &cellX, const int &cellY, uint16_t z, const wxString &operation, const wxString &id);
    void printQueue();
    void getDirection();
};