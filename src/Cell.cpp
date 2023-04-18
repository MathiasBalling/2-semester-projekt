// Header Files
#include "Cell.h"

Cell::Cell(int cellX, int cellY)
    : m_illuminated(false), m_piece(nullptr), m_cellX(cellX), m_cellY(cellY) {}

Piece *Cell::getPiece() { return m_piece; }

bool Cell::isIlluminated() { return m_illuminated; }

void Cell::setPiece(Piece *piece) {
  m_piece = piece;
  if (piece != nullptr) {
    piece->setCellX(m_cellX);
    piece->setCellY(m_cellY);
  }
}

void Cell::turnOff() { m_illuminated = false; }

void Cell::turnOn() { m_illuminated = true; }

bool Cell::hasPiece() { return m_piece != nullptr; }

int Cell::getCellX() { return m_cellX; }
int Cell::getCellY() { return m_cellY; }