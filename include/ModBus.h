#pragma once

// Header Files
#include "DeadPieceWindow.h"
#include "QueueWindow.h"

// Standard Libraries
#include <chrono>
#include <thread>
#include <vector>

// wxWidgets
#include <wx/wx.h>

// Modbus
#include <modbus.h>

class ModBus {
private:
  int m_xCorner, m_yCorner;
  int m_dX, m_dY;
  bool m_connected = false;
  std::vector<int> m_piecePosQueue;
  std::thread m_thread;
  modbus_t *m_mb;
  QueueWindow *m_queueWindow;
  DeadPieceWindow *m_deadPieceWindow;

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
  void moveQueue(const int &cellX, const int &cellY, uint16_t z,
                 const wxString &operation, const wxString &id);
  void printQueue();
  void getDirection(int xCornerBR, int yCornerBR, int xCornerBL, int yCornerBL);
  void setDeadPiece(const int &cellX, const int &cellY, const wxString &id);
};