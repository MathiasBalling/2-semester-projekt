// Header Files
#include "Cell.h"

Cell::Cell() : m_illuminated(false), m_piece(nullptr) {}

Piece *Cell::getPiece() { return m_piece; }

bool Cell::isIlluminated() { return m_illuminated; }

void Cell::setPiece(Piece *piece) { m_piece = piece; }

void Cell::turnOff() { m_illuminated = false; }

void Cell::turnOn() { m_illuminated = true; }

bool Cell::hasPiece() { return m_piece != nullptr; }

void Cell::setPos(int cellX, int cellY) {
  m_cellX = cellX;
  m_cellY = cellY;
}

int Cell::getCellX() { return m_cellX; }
int Cell::getCellY() { return m_cellY; }