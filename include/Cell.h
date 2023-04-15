#pragma once

// Header Files
#include "Piece.h"

class Cell {
public:
  Cell();
  bool isIlluminated();
  void turnOff();
  void turnOn();
  Piece *getPiece();
  void setPiece(Piece *piece);
  bool hasPiece();
  void setPos(int cellX, int cellY);
  int getCellX();
  int getCellY();

private:
  int m_cellX, m_cellY;
  Piece *m_piece;
  bool m_illuminated;
};