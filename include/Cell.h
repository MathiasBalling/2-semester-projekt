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

private:
  Piece *m_piece;
  bool m_illuminated;
};