// Header Files
#include "AI.h"
#include "wx/wx.h"

// Standard Libraries - for rand() and srand()
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <utility>

void AI::playTurn(Board *board) {
  // Choose the best move
  auto bestmove = bestMove(board);

  // Move the piece
  bestmove.second->move(bestmove.first->getCellX(), bestmove.first->getCellY(),
                        board);
  board->eraseAllIllumination();
  board->switchTurn();
}

int AI::evaluateBoard(Board *board) {
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
  return whiteValue - blackValue;
}

std::pair<Cell *, Piece *> AI::bestMove(Board *board) {
  int bestValue = 9999;
  std::pair<Cell *, Piece *> bestMove;

  // Find the best move
  for (auto piece : board->getPiecesMap()) {
    if (!piece.second->isAlive() || piece.second->getColor() != "black" ||
        !piece.second->canMove(board)) {
      continue;
    }
    piece.second->illuminatePaths(board);
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (!(board->getCellAt(x, y)->isIlluminated()))
          continue;
        // Move the piece
        int old_x = piece.second->getCellX();
        int old_y = piece.second->getCellY();
        board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
            ->setPiece(nullptr);
        Piece *dead_piece;
        if (board->isTherePiece(x, y)) {
          dead_piece = board->getPieceAt(x, y);
          dead_piece->setAlive(false);
        } else {
          dead_piece = nullptr;
        }
        board->getCellAt(x, y)->setPiece(piece.second);

        // Evaluate the tree
        int currentValue = minimax(board, 4, false);
        if (currentValue < bestValue) {
          bestValue = currentValue;
          bestMove = std::make_pair(board->getCellAt(x, y), piece.second);
        }
        // Undo the move
        if (dead_piece != nullptr) {
          dead_piece->setAlive(true);
          board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
              ->setPiece(dead_piece);
        } else {
          board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
              ->setPiece(nullptr);
        }
        board->getCellAt(old_x, old_y)->setPiece(piece.second);
      }
    }
  }
  return bestMove;
}

int AI::minimax(Board *board, int depth, bool isMaximizing) {
  // Check if the game is finished or the depth is 0
  if (depth == 0 || board->isGameFinished()) {
    return evaluateBoard(board);
  }

  if (isMaximizing) {
    int maxValue = -9999;

    for (auto piece : board->getPiecesMap()) {
      if (!piece.second->isAlive() || piece.second->getColor() != "white" ||
          !piece.second->canMove(board)) {
        continue;
      }
      piece.second->illuminatePaths(board);
      for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
          if (!(board->getCellAt(x, y)->isIlluminated()))
            continue;
          // Move the piece
          int old_x = piece.second->getCellX();
          int old_y = piece.second->getCellY();
          board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
              ->setPiece(nullptr);
          Piece *dead_piece;
          if (board->isTherePiece(x, y)) {
            dead_piece = board->getPieceAt(x, y);
            dead_piece->setAlive(false);
          } else {
            dead_piece = nullptr;
          }
          board->getCellAt(x, y)->setPiece(piece.second);

          // Recursively call minimax
          int currentValue = minimax(board, depth - 1, false);

          // Check if the current value is better than the best value
          if (currentValue > maxValue) {
            maxValue = currentValue;
          }
          // Undo the move
          if (dead_piece != nullptr) {
            dead_piece->setAlive(true);
            board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
                ->setPiece(dead_piece);
          } else {
            board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
                ->setPiece(nullptr);
          }
          board->getCellAt(old_x, old_y)->setPiece(piece.second);
        }
      }
    }
    return maxValue;
  } else {
    int minValue = 9999;

    for (auto piece : board->getPiecesMap()) {
      if (!piece.second->isAlive() || piece.second->getColor() != "black" ||
          !piece.second->canMove(board)) {
        continue;
      }
      piece.second->illuminatePaths(board);
      for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
          if (!(board->getCellAt(x, y)->isIlluminated()))
            continue;
          // Move the piece
          int old_x = piece.second->getCellX();
          int old_y = piece.second->getCellY();
          board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
              ->setPiece(nullptr);
          Piece *dead_piece;
          if (board->isTherePiece(x, y)) {
            dead_piece = board->getPieceAt(x, y);
            dead_piece->setAlive(false);
          } else {
            dead_piece = nullptr;
          }
          board->getCellAt(x, y)->setPiece(piece.second);

          // Recursively call minimax
          int currentValue = minimax(board, depth - 1, true);

          // Check if the current value is better than the best value
          if (currentValue < minValue) {
            minValue = currentValue;
          }

          // Undo the move
          if (dead_piece != nullptr) {
            dead_piece->setAlive(true);
            board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
                ->setPiece(dead_piece);
          } else {
            board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
                ->setPiece(nullptr);
          }
          board->getCellAt(old_x, old_y)->setPiece(piece.second);
        }
      }
    }
    return minValue;
  }
}