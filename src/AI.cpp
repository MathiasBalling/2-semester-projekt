// Header Files
#include "AI.h"
#include "wx/wx.h"

// Standard Libraries - for rand() and srand()
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <utility>

std::pair<Cell *, Piece *> AI::chooseRandomMove(Board *board) {
  int myAlivePiecesCount = 0;

  // Count the number of pieces that can move
  for (auto id_piece : board->getPiecesMap())
    myAlivePiecesCount += id_piece.second->isAlive() &&
                          id_piece.second->getColor() == board->getTurn() &&
                          id_piece.second->canMove(board);

  // Set the rand() to depend on the time
  srand(time(0));
  // int randNum = rand()%(max-min + 1) + min;
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
          wxLogMessage("Cell: %d, %d", x, y);
          possibleMoves -= board->getCellAt(x, y)->isIlluminated();
          if (possibleMoves == randMove) {
            board
                ->getCellAt(id_piece.second->getCellX(),
                            id_piece.second->getCellY())
                ->setPiece(nullptr);
            board->getCellAt(x, y)->setPiece(id_piece.second);
            wxLogMessage("Returns");
            return std::make_pair(board->getCellAt(x, y), id_piece.second);
          }
        }
      }
    }
  }
  return std::make_pair(nullptr, nullptr);
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

void AI::playTurn(Board *board) {
  // Choose the best move
  auto bestmove = minimax(board, 3, false);

  // Move the piece
  bestmove.first.second->move(bestmove.first.first->getCellX(),
                              bestmove.first.first->getCellY(), board);
  board->eraseAllIllumination();
  board->switchTurn();
}

std::pair<std::pair<Cell *, Piece *>, int> AI::minimax(Board *board, int depth,
                                                       bool isMaximizing) {
  std::cout << "Depth: " << depth << isMaximizing << std::endl;
  // Check if the game is finished or the depth is 0
  if (depth == 0 || board->isGameFinished()) {
    std::cout << "Break" << std::endl;
    return std::make_pair(std::make_pair(nullptr, nullptr),
                          evaluateBoard(board));
  }
  // Store the initial board of the node
  std::vector<std::pair<Cell *, Piece *>> initialBoard;
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      initialBoard.push_back(
          std::make_pair(board->getCellAt(x, y), board->getPieceAt(x, y)));
    }
  }
  if (isMaximizing) {
    int maxValue = -9999;
    std::pair<Cell *, Piece *> bestMove;
    bestMove = chooseRandomMove(board);

    for (auto piece : board->getPiecesMap()) {
      if (!piece.second->isAlive() || piece.second->getColor() != "white" ||
          !piece.second->canMove(board)) {
        continue;
      }
      piece.second->illuminatePaths(board);
      for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
          if (board->getCellAt(x, y)->isIlluminated()) {
            // Move the piece
            board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
                ->setPiece(nullptr);
            if (board->isTherePiece(x, y)) {
              board->getPieceAt(x, y)->setAlive(false);
            }
            board->getCellAt(x, y)->setPiece(piece.second);
            // Recursively call minimax
            auto currentValue = minimax(board, depth - 1, false);

            // Undo the move
            for (int i = 0; i < 64; i++) {
              board->getPieceAt(x, y)->setAlive(true);
              board
                  ->getCellAt(initialBoard[i].first->getCellX(),
                              initialBoard[i].first->getCellY())
                  ->setPiece(initialBoard[i].second);
            }

            // Check if the current value is better than the best value
            if (currentValue.second > maxValue) {
              std::cout << "Max: " << currentValue.second << std::endl;
              bestMove = std::make_pair(board->getCellAt(x, y), piece.second);
              maxValue = currentValue.second;
            }
          }
        }
      }
    }
    return std::make_pair(bestMove, maxValue);
  } else {
    int minValue = 9999;
    std::pair<Cell *, Piece *> bestMove;
    bestMove = chooseRandomMove(board);

    for (auto piece : board->getPiecesMap()) {
      if (!piece.second->isAlive() || piece.second->getColor() != "black" ||
          !piece.second->canMove(board)) {
        continue;
      }
      piece.second->illuminatePaths(board);
      for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
          if (board->getCellAt(x, y)->isIlluminated()) {
            // Move the piece
            board->getCellAt(piece.second->getCellX(), piece.second->getCellY())
                ->setPiece(nullptr);
            if (board->isTherePiece(x, y)) {
              board->getPieceAt(x, y)->setAlive(false);
            }
            board->getCellAt(x, y)->setPiece(piece.second);
            // Recursively call minimax
            auto currentValue = minimax(board, depth - 1, true);

            // Undo the move
            for (int i = 0; i < 64; i++) {
              board->getPieceAt(x, y)->setAlive(true);
              board
                  ->getCellAt(initialBoard[i].first->getCellX(),
                              initialBoard[i].first->getCellY())
                  ->setPiece(initialBoard[i].second);
            }

            // Check if the current value is better than the best value
            if (currentValue.second < minValue) {
              std::cout << "Min: " << currentValue.second << std::endl;
              bestMove = std::make_pair(board->getCellAt(x, y), piece.second);
              minValue = currentValue.second;
            }
          }
        }
      }
    }
    return std::make_pair(bestMove, minValue);
  }
}
