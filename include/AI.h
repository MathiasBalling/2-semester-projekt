#pragma once

// Header Files
#include "Board.h"

class AI {
public:
  static void playTurn(Board *board);

private:
  static Piece *chooseRandomPiece(Board *board);
  static void evaluateBoard(Board *board);
  static int whiteValue;
  static int blackValue;
};
