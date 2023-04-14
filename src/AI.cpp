// Header Files
#include "AI.h"
#include "wx/wx.h"

// Standard Libraries - for rand() and srand()
#include <cstdlib>
#include <time.h>

Piece *AI::chooseRandomPiece(Board *board) {
  int myAlivePiecesCount = 0;

  // Count the number of pieces that can move
  for (auto id_piece : board->getPiecesMap())
    myAlivePiecesCount += id_piece.second->isAlive() &&
                          id_piece.second->getColor() == board->getTurn() &&
                          id_piece.second->canMove(board);

  // Choose a random piece

  // Set the rand() to depend on the time
  srand(time(0));
  int count = rand() % myAlivePiecesCount + 1;
  for (auto id_piece : board->getPiecesMap()) {
    count -= id_piece.second->isAlive() &&
             id_piece.second->getColor() == board->getTurn() &&
             id_piece.second->canMove(board);
    if (count == 0)
      return id_piece.second;
  }
  return nullptr;
}

void AI::evaluateBoard(Board *board) {
  int whiteValue = 0;
  int blackValue = 0;

  // Count the number of pieces that can move
  for (auto id_piece : board->getPiecesMap()) {
    if (id_piece.second->isAlive()) {
      if (id_piece.second->getColor() == "white")
        whiteValue += id_piece.second->getValue();
      else
        blackValue += id_piece.second->getValue();
    }
  }
  wxLogMessage("White: %d, Black: %d", whiteValue, blackValue); 
}

void AI::playTurn(Board *board) {
  // Recive a random piece and illuminate its paths (the paths are the possible
  // moves)
  evaluateBoard(board);
  Piece *chosenPiece = chooseRandomPiece(board);
  chosenPiece->illuminatePaths(board);

  // Calculate the number of possible moves
  srand(time(0));
  int possibleMoves = 0;
  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
      possibleMoves += board->getCellAt(x, y)->isIlluminated();

  // Choose a random move
  int randMove = rand() % possibleMoves;
  for (int x = 0; x < 8 && possibleMoves != randMove; x++)
    for (int y = 0; y < 8 && possibleMoves != randMove; y++) {
      possibleMoves -= board->getCellAt(x, y)->isIlluminated();
      if (possibleMoves == randMove)
        chosenPiece->move(x, y, board);
    }
  board->eraseAllIllumination();
  board->switchTurn();
}
