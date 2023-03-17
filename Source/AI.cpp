#include "../Header/AI.h"
#include <cstdlib>
#include <time.h>

void AI::playTurn(Board* board)
{
	Piece* chosenPiece = chooseRandomPiece(board);
	chosenPiece->illuminatePaths(board);
	srand(time(0));
	int possibleMoves = 0;
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			possibleMoves += board->getCellAt(x, y)->isIlluminated();

	int randMove = rand() % possibleMoves;
	for (int x = 0; x < 8 && possibleMoves != randMove; x++)
		for (int y = 0; y < 8 && possibleMoves != randMove; y++)
		{
			possibleMoves -= board->getCellAt(x, y)->isIlluminated();
			if (possibleMoves == randMove)
				chosenPiece->move(x, y, board);
		}
	board->eraseAllIllumination();
	board->switchTurn();
}

Piece* AI::chooseRandomPiece(Board* board)
{
	srand(time(0));
	int myAlivePiecesCount = 0;
	for (auto id_piece : board->getPiecesMap())
		myAlivePiecesCount += id_piece.second->isAlive() && id_piece.second->getColor()==board->getTurn() && id_piece.second->canMove(board);
	int count = rand() % myAlivePiecesCount + 1;
	for (auto id_piece : board->getPiecesMap())
	{
		count -= id_piece.second->isAlive() && id_piece.second->getColor() == board->getTurn() && id_piece.second->canMove(board);
		if (count == 0)
			return id_piece.second;
	}
	return nullptr;
}