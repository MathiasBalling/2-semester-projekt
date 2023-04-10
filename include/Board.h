#pragma once

// wxWidgets
#include <wx/wx.h>

// Standard Libraries
#include <unordered_map>

// Header Files
#include "Cell.h"
#include "Robot.h"

class Board {
public:
  Board();
  ~Board();
  Piece *getPieceAt(int x, int y);
  const std::unordered_map<std::string, Piece *> &getPiecesMap();
  Cell *getCellAt(int cellX, int cellY);
  std::string getTurn();
  bool isThereEnemy(int cellX, int cellY);
  bool isThereAlly(int cellX, int cellY);
  bool isTherePiece(int cellX, int cellY);
  Piece *getSelectedPiece();
  void setSelectedPiece(Piece *piece);
  void switchTurn();
  void setEnemyIsAI(bool enemyIsAI);
  void eraseAllIllumination();
  void setGameFinished(bool gameFinished);
  bool isGameFinished();
  ModBus *mb = new ModBus();

private:
  std::string m_turn;
  std::unordered_map<std::string, Piece *> m_pieces;
  std::vector<std::vector<Cell *>> m_cells;
  Piece *m_selectedPiece;
  bool m_enemyIsAI = false;
  bool m_gameFinished;
  void initPieces();
  void initCells();
};