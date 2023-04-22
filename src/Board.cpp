// Header Files
#include "Board.h"
#include "AI.h"
#include "Piece.h"

// wxWidgets
#include <wx/bitmap.h>
#include <wx/msgdlg.h>

Board::Board() : m_turn{"white"}, m_gameFinished{false} {
  // Initialize the pieces and cells
  initPieces();
  initCells();
}

Board::~Board() { delete mb; }

const std::unordered_map<std::string, Piece *> &Board::getPiecesMap() {
  return m_pieces;
}

Piece *Board::getPieceAt(int cellX, int cellY) {
  return m_cells[cellX][cellY]->getPiece();
}

Piece *Board::getSelectedPiece() { return m_selectedPiece; }

void Board::setSelectedPiece(Piece *piece) { m_selectedPiece = piece; }

Cell *Board::getCellAt(int cellX, int cellY) { return m_cells[cellX][cellY]; }

std::string Board::getTurn() { return m_turn; }

void Board::switchTurn() {
  // If the game is finished, don't switch the turn
  if (m_gameFinished)
    return;

  // Switch the turn
  m_turn = m_turn == "white" ? "black" : "white";

  // If the enemy is an AI, let it play
  if (m_turn == "black" && m_enemyIsAI) {
    AI::playTurn(this);
  }
}

void Board::setGameFinished(bool gameFinished) {
  m_gameFinished = gameFinished;
  wxMessageBox(wxString("Game ended, " + m_turn + " wins."));
}

bool Board::isGameFinished() { return m_gameFinished; }

void Board::eraseAllIllumination() {
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
      getCellAt(x, y)->turnOff();
}

void Board::setEnemyIsAI(bool enemyIsAI) { m_enemyIsAI = enemyIsAI; }

bool Board::isThereEnemy(int cellX, int cellY) {

  return m_cells[cellX][cellY]->getPiece() != nullptr &&
         m_cells[cellX][cellY]->getPiece()->getColor() != m_turn;
}

bool Board::isThereAlly(int cellX, int cellY) {
  return m_cells[cellX][cellY]->getPiece() != nullptr &&
         m_cells[cellX][cellY]->getPiece()->getColor() == m_turn;
}

bool Board::isTherePiece(int cellX, int cellY) {
  return m_cells[cellX][cellY]->hasPiece();
}

void Board::initPieces() {
  // Initialize black pawns
  for (int x = 0; x < 8; x++) {
    wxImage image(
        "../images/black_pawn.png"); // Load the image of the black pawn
    Piece *pawn =
        new Pawn(x, 1, wxBitmap(image),
                 "B_Pawn_" + std::to_string(x)); // Create the black pawns
    m_pieces[pawn->getId()] = pawn;              // Add the pawn to the map
    pawn->setValue(10);
  }
  // Inititialize white pawns
  for (int x = 0; x < 8; x++) {
    wxImage image(
        "../images/white_pawn.png"); // Load the image of the white pawn
    Piece *pawn =
        new Pawn(x, 6, wxBitmap(image),
                 "W_Pawn_" + std::to_string(x)); // Create the white pawns
    m_pieces[pawn->getId()] = pawn;              // Add the pawn to the map
    pawn->setValue(10);
  }
  // Initialize the other pieces
  std::string ids[] = {"Rook_0", "Knight_0", "Bishop_0", "Queen",
                       "King",   "Bishop_1", "Knight_1", "Rook_1"};
  std::string colors[] = {"W", "B"};
  for (int x = 0; x < 8; x++) // Loop through the ids
  {
    for (auto &color : colors) // Loop through the colors
    {
      Piece *piece;
      std::string imageName =
          color == "W" ? "white" : "black"; // Set start of the image name
      switch (ids[x][0]) {
      case 'R':                   // If the id starts with R, it's a rook
        imageName += "_rook.png"; // Set the image name
        piece = new Rook(x, color == "W" ? 7 : 0,
                         wxBitmap(wxImage("../images/" + imageName)),
                         color + "_" + ids[x]);
        piece->setValue(50);
        break;
      case 'K': // If the id starts with K, it's a knight or a king
        if (ids[x][1] == 'i') {
          imageName += "_king.png"; // Set the image name
          piece = new King(x, color == "W" ? 7 : 0,
                           wxBitmap(wxImage("../images/" + imageName)),
                           color + "_" + ids[x]);
          piece->setValue(900);
        } else {
          imageName += "_knight.png"; // Set the image name
          piece = new Knight(x, color == "W" ? 7 : 0,
                             wxBitmap(wxImage("../images/" + imageName)),
                             color + "_" + ids[x]);
          piece->setValue(30);
        }
        break;
      case 'B':                     // If the id starts with B, it's a bishop
        imageName += "_bishop.png"; // Set the image name
        piece = new Bishop(x, color == "W" ? 7 : 0,
                           wxBitmap(wxImage("../images/" + imageName)),
                           color + "_" + ids[x]);
        piece->setValue(30);
        break;
      case 'Q':                    // If the id starts with Q, it's a queen
        imageName += "_queen.png"; // Set the image name
        piece = new Queen(x, color == "W" ? 7 : 0,
                          wxBitmap(wxImage("../images/" + imageName)),
                          color + "_" + ids[x]);
        piece->setValue(90);
      }
      m_pieces[piece->getId()] = piece;
    }
  }
}

void Board::initCells() {
  std::vector<Cell *> empty(8);
  // Make vector of empty cells
  for (int i = 0; i < 8; i++) {
    m_cells.push_back(empty);
    for (int j = 0; j < 8; j++) {
      m_cells[i][j] = new Cell(i, j);
    }
  }

  // Add the pieces to the cells
  for (auto &it : m_pieces) {
    Piece *piece = it.second;
    int x = piece->getCellX();
    int y = piece->getCellY();
    m_cells[x][y]->setPiece(piece);
  }
}

void Board::addDeadPiece(Piece *piece, std::string color) {
  if (color == "black")
    m_deadBlackPieces.push_back(piece);
  else {
    m_deadWhitePieces.push_back(piece);
  }
}

std::vector<Piece *> Board::getDeadPieces(std::string color) {
  if (color == "black")
    return m_deadBlackPieces;
  else {
    return m_deadWhitePieces;
  }
}