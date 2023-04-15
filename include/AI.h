#pragma once

// Header Files
#include "Board.h"
#include <utility>

class AI {
public:
  static void playTurn(Board *board);

private:
  static std::pair<Cell *, Piece *> chooseRandomMove(Board *board);
  static int evaluateBoard(Board *board);
    static std::pair<Cell* , Piece*> bestmove(Board *board);
  static int minimax(Board *board, int depth, bool isMaximizing);
};
