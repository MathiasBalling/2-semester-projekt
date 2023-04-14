#pragma once

// Header Files
#include "Board.h"

class AI {
public:
  static void playTurn(Board *board);

private:
  static void chooseRandomMove(Board *board);
  static void evaluateBoard(Board *board);
};
