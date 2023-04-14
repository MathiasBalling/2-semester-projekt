// Header Files
#include "AI.h"
#include "wx/wx.h"

// Standard Libraries - for rand() and srand()
#include <cstdlib>
#include <time.h>
#include <utility>

void AI::chooseRandomMove(Board *board) {
  int myAlivePiecesCount = 0;

  // Count the number of pieces that can move
  for (auto id_piece : board->getPiecesMap())
    myAlivePiecesCount += id_piece.second->isAlive() &&
                          id_piece.second->getColor() == board->getTurn() &&
                          id_piece.second->canMove(board);

  // Set the rand() to depend on the time
  srand(time(0));
  int count = rand() % myAlivePiecesCount + 1;
  for (auto id_piece : board->getPiecesMap()) {
    count -= id_piece.second->isAlive() &&
             id_piece.second->getColor() == board->getTurn() &&
             id_piece.second->canMove(board);
    if (count == 0) {
      id_piece.second->illuminatePaths(board);
      // Calculate the number of possible moves
      srand(time(0));
      int possibleMoves = 0;
      for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
          possibleMoves += board->getCellAt(x, y)->isIlluminated();

      wxLogMessage("Piece: %s", id_piece.second->getId());
      // Choose a random move
      int randMove = rand() % possibleMoves;
      for (int x = 0; x < 8 && possibleMoves != randMove; x++) {
        for (int y = 0; y < 8 && possibleMoves != randMove; y++) {
          possibleMoves -= board->getCellAt(x, y)->isIlluminated();
          if (possibleMoves == randMove)
            id_piece.second->move(x, y, board);
        }
      }
      break;
    }
  }
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
  int bestValue = 0;
  std::pair<Piece *, Piece *> bestMove;
  bestMove = std::make_pair(nullptr, nullptr);
  for (auto piece : board->getPiecesMap()) {
    if (!piece.second->isAlive() ||
        piece.second->getColor() != board->getTurn() ||
        !piece.second->canMove(board)) {
      continue;
    }
    piece.second->illuminatePaths(board);
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (board->getCellAt(x, y)->isIlluminated() &&
            board->isThereEnemy(x, y)) {
          Piece *target = board->getCellAt(x, y)->getPiece();
          if (target->getValue() > bestValue) {
            bestMove = std::make_pair(target, piece.second);
            bestValue = target->getValue();
          }
        }
      }
    }
  }
  if (bestValue != 0) {
    bestMove.second->move(bestMove.first->getCellX(),
                          bestMove.first->getCellY(), board);
  } else {
    chooseRandomMove(board);
  }

  evaluateBoard(board);

  board->eraseAllIllumination();
  board->switchTurn();
}
