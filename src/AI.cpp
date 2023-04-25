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
int calculatedMoves;

void AI::playTurn(Board *board) {
  calculatedMoves = 0;
  // Choose the best move
  auto bestmove = bestMove(board);

  // Move the piece
  bestmove.second->move(bestmove.first->getCellX(), bestmove.first->getCellY(),
                        board);
  std::cout << "AI calculated " << calculatedMoves << " moves" << std::endl;
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
    if (!piece.second->isAlive() ||
        piece.second->getColor() != board->getTurn() ||
        !piece.second->canMove(board)) {
      continue;
    }
    piece.second->illuminatePaths(board);
    std::vector<std::pair<int, int>> moves;
    for (int x = 0; x < 8; x++) {
      for (int y = 0; y < 8; y++) {
        if (board->getCellAt(x, y)->isIlluminated())
          moves.push_back(std::make_pair(x, y));
      }
    }
    for (auto move : moves) {
      calculatedMoves++;
      // Move the piece
      int old_x = piece.second->getCellX();
      int old_y = piece.second->getCellY();
      board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
          ->setPiece(nullptr);
      Piece *dead_piece;
      if (board->isTherePiece(move.first, move.second)) {
        dead_piece = board->getPieceAt(move.first, move.second);
        dead_piece->setAlive(false);
      } else {
        dead_piece = nullptr;
      }
      board->getCellAt(move.first, move.second)->setPiece(piece.second);

      // Evaluate the tree
      int currentValue = minimax(board, 4, true, -9999, 9999);
      // std::cout << "Current value: " << currentValue << std::endl;
      if (currentValue < bestValue) {
        bestValue = currentValue;
        bestMove = std::make_pair(board->getCellAt(move.first, move.second),
                                  piece.second);
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
  // std::cout << "Best value: " << bestValue << std::endl;
  return bestMove;
}

int AI::minimax(Board *board, int depth, bool isMaximizing, int alpha,
                int beta) {
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
      std::vector<std::pair<int, int>> moves;
      piece.second->illuminatePaths(board);
      for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
          if (board->getCellAt(x, y)->isIlluminated())
            moves.push_back(std::make_pair(x, y));
        }
      }
      for (auto move : moves) {
        calculatedMoves++;
        // Move the piece
        int old_x = piece.second->getCellX();
        int old_y = piece.second->getCellY();
        board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
            ->setPiece(nullptr);
        Piece *dead_piece = nullptr;
        if (board->isTherePiece(move.first, move.second)) {
          dead_piece = board->getPieceAt(move.first, move.second);
          dead_piece->setAlive(false);
        }
        board->getCellAt(move.first, move.second)->setPiece(piece.second);

        // Recursively call minimax
        int currentValue = minimax(board, depth - 1, false, alpha, beta);

        // Check if the current value is better than the best value
        maxValue = std::max(maxValue, currentValue);
        // Undo the move
        if (dead_piece != nullptr) {
          dead_piece->setAlive(true);
          board->getCellAt(move.first, move.second)->setPiece(dead_piece);
        } else {
          board->getCellAt(move.first, move.second)->setPiece(nullptr);
        }
        board->getCellAt(old_x, old_y)->setPiece(piece.second);

        alpha = std::max(alpha, maxValue);
        if (beta <= alpha)
          break;
      }
      if (beta <= alpha)
        break;
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
      std::vector<std::pair<int, int>> moves;
      for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
          if (board->getCellAt(x, y)->isIlluminated())
            moves.push_back(std::make_pair(x, y));
        }
      }
      for (auto move : moves) {
        calculatedMoves++;
        // Move the piece
        int old_x = piece.second->getCellX();
        int old_y = piece.second->getCellY();
        board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
            ->setPiece(nullptr);
        Piece *dead_piece = nullptr;
        if (board->isTherePiece(move.first, move.second)) {
          dead_piece = board->getPieceAt(move.first, move.second);
          dead_piece->setAlive(false);
        }
        board->getCellAt(move.first, move.second)->setPiece(piece.second);

        // Recursively call minimax
        int currentValue = minimax(board, depth - 1, true, alpha, beta);

        // Check if the current value is better than the best value
        minValue = std::min(minValue, currentValue);

        // Undo the move
        if (dead_piece != nullptr) {
          dead_piece->setAlive(true);
          board->getCellAt(move.first, move.second)->setPiece(dead_piece);
        } else {
          board->getCellAt(move.first, move.second)->setPiece(nullptr);
        }
        board->getCellAt(old_x, old_y)->setPiece(piece.second);

        beta = std::min(beta, minValue);
        if (beta <= alpha)
          break;
      }
      if (beta <= alpha)
        break;
    }
    return minValue;
  }
}