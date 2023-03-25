// Header Files
#include "../Header/Cell.h"

Cell::Cell()
	: _illuminated(false), _piece(nullptr)
{
}

Piece *Cell::getPiece()
{
	return _piece;
}

bool Cell::isIlluminated()
{
	return _illuminated;
}

void Cell::setPiece(Piece *piece)
{
	this->_piece = piece;
}

void Cell::turnOff()
{
	_illuminated = false;
}

void Cell::turnOn()
{
	_illuminated = true;
}

bool Cell::hasPiece()
{
	return _piece != nullptr;
}