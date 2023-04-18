// Header Files
#include "Piece.h"
#include "Board.h"

// wxWidgets
#include <wx/bitmap.h>

// Standard Libraries
#include <string>

Piece::Piece(int cellX, int cellY, wxBitmap image, std::string id) {
  m_cellX = cellX;
  m_cellY = cellY;
  m_image = image;
  m_id = id;
  m_color = id[0] == 'W' ? "white" : "black";
  m_alive = true;
}

std::string Piece::getId() { return m_id; }

int Piece::getCellX() { return m_cellX; }

int Piece::getCellY() { return m_cellY; }

void Piece::setCellX(int x) { m_cellX = x; }

void Piece::setCellY(int y) { m_cellY = y; }

wxBitmap Piece::getImage() { return m_image; }

std::string Piece::getColor() { return m_color; }

bool Piece::isAlive() { return m_alive; }

void Piece::setAlive(bool isAlive) { m_alive = isAlive; }

void Piece::setValue(int value) { m_value = value; }

int Piece::getValue() { return m_value; }

bool Piece::canMove(Board *board) {
  //
  illuminatePaths(board);
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      // Check if piece has any illuminated cells
      if (board->getCellAt(x, y)->isIlluminated()) {
        board->eraseAllIllumination();
        return true;
      }
    }
  }
  // If there was no illuminated cells then the piece can't move
  board->eraseAllIllumination();
  return false;
}

void Piece::move(int targetX, int targetY, Board *board) {
  // Check if there's a piece in the target cell
  if (board->isTherePiece(targetX, targetY)) {
    board->getPieceAt(targetX, targetY)->setAlive(false);

    // Check if the piece is a king	and set the game as finished
    if (board->getPieceAt(targetX, targetY)->getId().find("King") !=
        std::string::npos)
      board->setGameFinished(true);
  }
  // Check if there's a piece in the target cell
  if (board->isTherePiece(targetX, targetY)) {
    std::string tempid = board->getPieceAt(targetX, targetY)->getId();
    // Take the piece from the target cell
    board->mb->moveQueue(targetX, targetY, 200, "Take dead piece", tempid);
    // Then move to the position outside the board
    board->mb->moveQueue(3, 9, 200, "To Outside Board", tempid);
    // Get piece from initial cell
    board->mb->moveQueue(m_cellX, m_cellY, 200, "From", m_id);
    // Then move to the target cell
    board->mb->moveQueue(targetX, targetY, 200, "To", m_id);
  } else {
    // If there's no piece in the target cell, just take the piece from the
    // initial cell
    board->mb->moveQueue(m_cellX, m_cellY, 200, "From", m_id);
    // Then move to the target cell
    board->mb->moveQueue(targetX, targetY, 200, "To", m_id);
  }
  // Move piece on the board
  board->getCellAt(m_cellX, m_cellY)->setPiece(nullptr);
  m_cellX = targetX;
  m_cellY = targetY;
  board->getCellAt(targetX, targetY)->setPiece(this);
}

// Create the pieces and set their possible moves
Pawn::Pawn(int cellX, int cellY, wxBitmap image, std::string id)
    : Piece(cellX, cellY, image, id) {}

void Pawn::illuminatePaths(Board *board) {
  int sign = m_color == "white" ? 1 : -1;
  std::pair<int, int> offsets[3] = {
      {-1, -1 * sign}, {0, -1 * sign}, {1, -1 * sign}};

  for (auto offset : offsets) {
    if (m_cellX + offset.first >= 0 && m_cellX + offset.first < 8 &&
        m_cellY + offset.second >= 0 && m_cellY + offset.second < 8) {
      if (offset.first == 0) {
        // Check if there's a piece in front of the pawn
        if (!board->isTherePiece(m_cellX, m_cellY + offset.second)) {
          board->getCellAt(m_cellX, m_cellY + offset.second)->turnOn();
        }
      } else {
        // Check if there's an enemy in the diagonal cells
        if (board->isThereEnemy(m_cellX + offset.first,
                                m_cellY + offset.second)) {
          board->getCellAt(m_cellX + offset.first, m_cellY + offset.second)
              ->turnOn();
        }
      }
    }
  }
  // Check if it's the pawn's first move
  if ((m_cellY == 6 && m_color == "white" &&
       !(board->isTherePiece(m_cellX, 4)) &&
       !(board->isTherePiece(m_cellX, 5))) ||
      (m_cellY == 1 && m_color == "black" &&
       !(board->isTherePiece(m_cellX, 3)) &&
       !(board->isTherePiece(m_cellX, 2))))
    board->getCellAt(m_cellX, m_cellY - 2 * sign)->turnOn();
}
Rook::Rook(int cellX, int cellY, wxBitmap image, std::string id)
    : Piece(cellX, cellY, image, id) {}

void Rook::illuminatePaths(Board *board) {
  // Upward direction
  int x, y;
  for (y = m_cellY - 1; y >= 0 && !board->isTherePiece(m_cellX, y); y--)
    board->getCellAt(m_cellX, y)->turnOn();

  if (y >= 0 && board->isThereEnemy(m_cellX, y))
    board->getCellAt(m_cellX, y)->turnOn();

  // Downward direction
  for (y = m_cellY + 1; y < 8 && !board->isTherePiece(m_cellX, y); y++)
    board->getCellAt(m_cellX, y)->turnOn();

  if (y < 8 && board->isThereEnemy(m_cellX, y))
    board->getCellAt(m_cellX, y)->turnOn();

  // Left direction
  for (x = m_cellX - 1; x >= 0 && !board->isTherePiece(x, m_cellY); x--)
    board->getCellAt(x, m_cellY)->turnOn();

  if (x >= 0 && board->isThereEnemy(x, m_cellY))
    board->getCellAt(x, m_cellY)->turnOn();

  // Right direction
  for (x = m_cellX + 1; x < 8 && !board->isTherePiece(x, m_cellY); x++)
    board->getCellAt(x, m_cellY)->turnOn();

  if (x < 8 && board->isThereEnemy(x, m_cellY))
    board->getCellAt(x, m_cellY)->turnOn();
}

Knight::Knight(int cellX, int cellY, wxBitmap image, std::string id)
    : Piece(cellX, cellY, image, id) {}

void Knight::illuminatePaths(Board *board) {
  std::pair<int, int> offsets[8] = {{-1, -2}, {-1, 2}, {-2, 1}, {-2, -1},
                                    {1, -2},  {1, 2},  {2, -1}, {2, 1}};
  for (auto offset : offsets) {
    if (m_cellX + offset.first >= 0 && m_cellX + offset.first <= 7 &&
        m_cellY + offset.second >= 0 && m_cellY + offset.second <= 7 &&
        !board->isThereAlly(m_cellX + offset.first, m_cellY + offset.second))
      board->getCellAt(m_cellX + offset.first, m_cellY + offset.second)
          ->turnOn();
  }
}

Bishop::Bishop(int cellX, int cellY, wxBitmap image, std::string id)
    : Piece(cellX, cellY, image, id) {}

void Bishop::illuminatePaths(Board *board) {
  // Top-left direction
  int x, y;
  for (x = m_cellX - 1, y = m_cellY - 1;
       x >= 0 && y >= 0 && !board->isTherePiece(x, y); x--, y--)
    board->getCellAt(x, y)->turnOn();

  if (x >= 0 && y >= 0 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();

  // Top-right direction
  for (x = m_cellX + 1, y = m_cellY - 1;
       x < 8 && y >= 0 && !board->isTherePiece(x, y); x++, y--)
    board->getCellAt(x, y)->turnOn();

  if (x < 8 && y >= 0 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();

  // Bottom-left direction
  for (x = m_cellX - 1, y = m_cellY + 1;
       x >= 0 && y < 8 && !board->isTherePiece(x, y); x--, y++)
    board->getCellAt(x, y)->turnOn();

  if (x >= 0 && y < 8 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();

  // Bottom-right direction
  for (x = m_cellX + 1, y = m_cellY + 1;
       x < 8 && y < 8 && !board->isTherePiece(x, y); x++, y++)
    board->getCellAt(x, y)->turnOn();

  if (x < 8 && y < 8 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();
}

Queen::Queen(int cellX, int cellY, wxBitmap image, std::string id)
    : Piece(cellX, cellY, image, id) {}

void Queen::illuminatePaths(Board *board) {
  // Top-left direction
  int x, y;
  for (x = m_cellX - 1, y = m_cellY - 1;
       x >= 0 && y >= 0 && !board->isTherePiece(x, y); x--, y--)
    board->getCellAt(x, y)->turnOn();

  if (x >= 0 && y >= 0 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();

  // Top-right direction
  for (x = m_cellX + 1, y = m_cellY - 1;
       x < 8 && y >= 0 && !board->isTherePiece(x, y); x++, y--)
    board->getCellAt(x, y)->turnOn();

  if (x < 8 && y >= 0 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();

  // Bottom-left direction
  for (x = m_cellX - 1, y = m_cellY + 1;
       x >= 0 && y < 8 && !board->isTherePiece(x, y); x--, y++)
    board->getCellAt(x, y)->turnOn();

  if (x >= 0 && y < 8 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();

  // Bottom-right direction
  for (x = m_cellX + 1, y = m_cellY + 1;
       x < 8 && y < 8 && !board->isTherePiece(x, y); x++, y++)
    board->getCellAt(x, y)->turnOn();

  if (x < 8 && y < 8 && board->isThereEnemy(x, y))
    board->getCellAt(x, y)->turnOn();

  // Upward direction
  for (y = m_cellY - 1; y >= 0 && !board->isTherePiece(m_cellX, y); y--)
    board->getCellAt(m_cellX, y)->turnOn();

  if (y >= 0 && board->isThereEnemy(m_cellX, y))
    board->getCellAt(m_cellX, y)->turnOn();

  // Downward direction
  for (y = m_cellY + 1; y < 8 && !board->isTherePiece(m_cellX, y); y++)
    board->getCellAt(m_cellX, y)->turnOn();

  if (y < 8 && board->isThereEnemy(m_cellX, y))
    board->getCellAt(m_cellX, y)->turnOn();

  // Left direction
  for (x = m_cellX - 1; x >= 0 && !board->isTherePiece(x, m_cellY); x--)
    board->getCellAt(x, m_cellY)->turnOn();

  if (x >= 0 && board->isThereEnemy(x, m_cellY))
    board->getCellAt(x, m_cellY)->turnOn();

  // Right direction
  for (x = m_cellX + 1; x < 8 && !board->isTherePiece(x, m_cellY); x++)
    board->getCellAt(x, m_cellY)->turnOn();

  if (x < 8 && board->isThereEnemy(x, m_cellY))
    board->getCellAt(x, m_cellY)->turnOn();
}

King::King(int cellX, int cellY, wxBitmap image, std::string id)
    : Piece(cellX, cellY, image, id) {}

void King::illuminatePaths(Board *board) {
  std::pair<int, int> offsets[8] = {{-1, -1}, {-1, 1}, {-1, 0}, {0, -1},
                                    {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  for (auto offset : offsets) {
    if (m_cellX + offset.first >= 0 && m_cellX + offset.first < 8 &&
        m_cellY + offset.second >= 0 && m_cellY + offset.second < 8 &&
        !board->isThereAlly(m_cellX + offset.first, m_cellY + offset.second))
      board->getCellAt(m_cellX + offset.first, m_cellY + offset.second)
          ->turnOn();
  }
}
