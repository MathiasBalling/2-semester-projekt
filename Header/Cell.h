#pragma once

// Header Files
#include "../Header/Pieces.h"

class Cell
{
public:
	Cell();
	bool isIlluminated();
	void turnOff();
	void turnOn();
	Piece* getPiece();
	void setPiece(Piece* piece);
	bool hasPiece();
	

private:
	Piece* _piece;
	bool _illuminated;

};