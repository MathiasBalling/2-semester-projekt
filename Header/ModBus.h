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
    int m_dX = 40, m_dY = 40;
    bool m_connected = false;
    std::vector<int> m_piecePosQueue;
    std::thread m_thread;
    modbus_t *m_mb;
    QueueWindow *m_queueWindow;

public:
    ModBus();
    ~ModBus();
    int getX(int cellY);
    int getY(int cellY);
    void setXval(int val);
    void setYval(int val);
    void setZval(int val);
    void setCO(uint16_t val);
    int getDO();
    bool isConnected();
    void movePiece();
    bool shouldRun();
    void moveQueue(const int &cellX, const int &cellY, uint16_t z, const wxString &operation, const wxString &id);
    void printQueue();
    void getDirection();
};