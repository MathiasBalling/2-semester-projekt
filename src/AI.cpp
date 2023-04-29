// Header Files
#include "AI.h"
#include "wx/wx.h"

// Standard Libraries - for rand() and srand()
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <utility>
#include <vector>

void AI::playTurn(Board *board) {
  // Choose the best move
  auto bestmove = bestMove(board);

  // // Move the piece
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
  int bestforWhite = -9999;
  std::pair<Cell *, Piece *> bestMove;

  // Find the best move
  for (auto piece : board->getPiecesMap()) {
    if (!piece.second->isAlive() || piece.second->getColor() != "black" ||
        !piece.second->canMove(board)) {
      continue;
    }
    piece.second->illuminatePaths(board);
    std::vector<std::pair<int, int>> moves;
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (board->getCellAt(x, y)->isIlluminated()) {
          moves.push_back(std::make_pair(x, y));
        }
      }
    }
    for (auto move : moves) {
      // Move the piece
      int pieceX = piece.second->getCellX();
      int pieceY = piece.second->getCellY();
      Piece *deadPiece =
          piece.second->tempMovePiece(move.first, move.second, board);
      if (deadPiece != nullptr) {
        if (deadPiece->getId().find("King") != std::string::npos) {
          board->setGameFinished(true);
        }
      }

      // Evaluate the tree
      int currentValue = minimax(board, 4, true, -9999, 9999);
      if (currentValue < bestValue) {
        bestValue = currentValue;
        bestMove = std::make_pair(board->getCellAt(move.first, move.second),
                                  piece.second);
      }
      // Undo the move
      piece.second->tempMoveUndo(pieceX, pieceY, deadPiece, board);
      if (board->isGameFinished()) {
        board->setGameFinished(false);
      }
    }
  }
  return bestMove;
}

int AI::minimax(Board *board, int depth, bool isMaximizing, int alpha,
                int beta) {
  std::pair<int, int> bestmove;
  // Check if the game is finished or the depth is 0
  if (depth == 0 || board->isGameFinished()) {
    return evaluateBoard(board);
  }
  int value = isMaximizing ? -9999 : 9999;
  std::string color = isMaximizing ? "white" : "black";

  for (auto piece : board->getPiecesMap()) {
    if (!piece.second->isAlive() || piece.second->getColor() != color ||
        !piece.second->canMove(board)) {
      continue;
    }
    std::vector<std::pair<int, int>> moves;
    piece.second->illuminatePaths(board);
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (board->getCellAt(x, y)->isIlluminated())
          moves.push_back(std::make_pair(x, y));
      }
    }
    for (auto move : moves) {
      // Move the piece
      int pieceX = piece.second->getCellX();
      int pieceY = piece.second->getCellY();
      Piece *deadPiece =
          piece.second->tempMovePiece(move.first, move.second, board);
      if (deadPiece != nullptr) {
        if (deadPiece->getId().find("King") != std::string::npos) {
          board->setGameFinished(true);
        }
      }

      if (isMaximizing) {
        // Recursively call minimax
        int currentValue = minimax(board, depth - 1, false, alpha, beta);

        // Check if the current value is better than the best value
        if (currentValue > value) {
          bestmove = move;
        }
        value = std::max(value, currentValue);
        alpha = std::max(alpha, value);
      } else {
        // Recursively call minimax
        int currentValue = minimax(board, depth - 1, true, alpha, beta);
        if (currentValue < value) {
          bestmove = move;
        }
        // Check if the current value is better than the best value
        value = std::min(value, currentValue);
        beta = std::min(beta, value);
      }

      // Undo the move
      piece.second->tempMoveUndo(pieceX, pieceY, deadPiece, board);
      if (board->isGameFinished()) {
        board->setGameFinished(false);
      }

      if (beta <= alpha)
        break;
    }
    if (beta <= alpha)
      break;
  }
  return value;
}