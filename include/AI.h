#pragma once

// Header Files
#include "Board.h"
#include <utility>

class AI {
public:
  static void playTurn(Board *board);

private:
  static int evaluateBoard(Board *board);
  static std::pair<Cell *, Piece *> bestMove(Board *board);
  static int minimax(Board *board, int depth, bool isMaximizing, int alpha,
                     int beta);
};
