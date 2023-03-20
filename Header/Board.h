#pragma once
#include "../Header/Board.fwd.h"
#include "../Header/Piece.fwd.h"
#include <wx/wx.h>
#include <unordered_map>
#include "../Header/UR5.h"
#include "../Header/Cell.h"

class Board
{
public:
	Board();
	Piece *getPieceAt(int x, int y);
	const std::unordered_map<std::string, Piece *> &getPiecesMap();
	Cell *getCellAt(int cellX, int cellY);
	std::string turn;
	std::string getTurn();
	bool isThereEnemy(int cellX, int cellY);
	bool isThereAlly(int cellX, int cellY);
	bool isTherePiece(int cellX, int cellY);
	Piece *getSelectedPiece();
	void setSelectedPiece(Piece *piece);
	void switchTurn();
	void setEnemyIsAI(bool enemyIsAI);
	void eraseAllIllumination();
	void setGameFinished(bool gameFinished);
	bool isGameFinished();
	UR5 ur;

private:
	std::unordered_map<std::string, Piece *> pieces;
	std::vector<std::vector<Cell *>> cells;
	Piece *selectedPiece;
	bool enemyIsAI = false;
	bool gameFinished;
	void initPieces();
	void initCells();
};