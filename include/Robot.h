#pragma once

// Header Files
#include "ChessFrame.h"
#include "ControlWindow.h"

// Standard Libraries
#include <chrono>
#include <thread>
#include <vector>

// wxWidgets
#include <wx/wx.h>

// Modbus
#include "serialib.h"
#include <modbus.h>

class Robot {
private:
  int m_xCorner, m_yCorner, m_xCornerBR, m_yCornerBR, m_xCornerBL, m_yCornerBL;
  int m_dX, m_dY;
  uint16_t m_zHeight = 200;
  bool m_connected = true;
  std::vector<int> m_piecePosQueue;
  std::thread m_thread;
  modbus_t *m_mb;
  ControlWindow *m_controlWindow;
  wxDialog *m_dialog;
  Board *m_board;
  void makeDialog();
  serialib m_serial;

public:
  Robot(Board *board);
  ~Robot();
  std::pair<int, int> getXY(const int &cellX, const int &cellY);
  void setXval(int val);
  void setYval(int val);
  void setZval(int val);
  void setCO(uint16_t val);
  int getDO();
  bool isConnected();
  void movePiece();
  bool shouldRun();
  void moveQueue(const int &cellX, const int &cellY, const wxString &operation,
                 const wxString &id);
  void getDirection(int xCornerBR, int yCornerBR, int xCornerBL, int yCornerBL);
  void setDeadPiece(const int &cellX, const int &cellY, const wxString &id);
};
