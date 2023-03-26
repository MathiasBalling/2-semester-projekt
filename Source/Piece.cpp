// Header Files
#include "../Header/Pieces.h"
#include "../Header/Board.h"

// wxWidgets
#include <wx/bitmap.h>

// Standard Libraries
#include <string>

Piece::Piece(int cellX, int cellY, wxBitmap image, std::string id)
{
	_cellX = cellX;
	_cellY = cellY;
	_image = image;
	_id = id;
	_color = id[0] == 'W' ? "white" : "black";
	_alive = true;
}

std::string Piece::getId()
{
	return _id;
}

int Piece::getCellX()
{
	return _cellX;
}

int Piece::getCellY()
{
	return _cellY;
}

void Piece::setCellX(int x)
{
	_cellX = x;
}

void Piece::setCellY(int y)
{
	_cellY = y;
}

wxBitmap Piece::getImage()
{
	return _image;
}

std::string Piece::getColor()
{
	return _color;
}

bool Piece::isAlive()
{
	return _alive;
}

void Piece::setAlive(bool isAlive)
{
	_alive = isAlive;
}

bool Piece::canMove(Board *board)
{
	//
	illuminatePaths(board);
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			// Check if piece has any illuminated cells
			if (board->getCellAt(x, y)->isIlluminated())
			{
				board->eraseAllIllumination();
				return true;
			}
		}
	}
	// If there was no illuminated cells then the piece can't move
	board->eraseAllIllumination();
	return false;
}

void Piece::move(int targetX, int targetY, Board *board)
{
	// Check if there's a piece in the target cell
	if (board->isTherePiece(targetX, targetY))
	{
		board->getPieceAt(targetX, targetY)->setAlive(false);

		// Check if the piece is a king	and set the game as finished
		if (board->getPieceAt(targetX, targetY)->getId().find("King") != std::string::npos)
			board->setGameFinished(true);
	}
	// Send coordinates to the log
	wxLogMessage("%s From: x=%d y=%d\tTo: x=%d y=%d", _id, _cellX, _cellY, targetX, targetY);

	// Check if Modbus is connected
	if (board->mb->isConnected())
	{
		// Check if there's a piece in the target cell
		if (board->isTherePiece(targetX, targetY))
		{
			// Take the piece from the target cell
			board->mb->moveQueue(targetX, targetY, 200);
			// Then move to the position outside the board
			board->mb->moveQueue(3, 9, 200);
			// Get piece from initial cell
			board->mb->moveQueue(_cellX, _cellY, 200);
			// Then move to the target cell
			board->mb->moveQueue(targetX, targetY, 200);
		}
		else
		{
			// If there's no piece in the target cell, just take the piece from the initial cell
			board->mb->moveQueue(_cellX, _cellY, 200);
			// Then move to the target cell
			board->mb->moveQueue(targetX, targetY, 200);
		}
	}
	else
	{
		wxLogMessage("Can't send coordinates to UR5!");
	}

	// Move piece on the board
	board->getCellAt(_cellX, _cellY)->setPiece(nullptr);
	_cellX = targetX;
	_cellY = targetY;
	board->getCellAt(targetX, targetY)->setPiece(this);
}

// Create the pieces and set their possible moves
Pawn::Pawn(int cellX, int cellY, wxBitmap image, std::string id)
	: Piece(cellX, cellY, image, id)
{
}

void Pawn::illuminatePaths(Board *board)
{
	int sign = 1;
	if (_color == "black")
		sign = -1;
	std::pair<int, int> offsets[3] = {{-1, -1 * sign}, {0, -1 * sign}, {1, -1 * sign}};

	for (auto offset : offsets)
	{
		if (_cellX + offset.first >= 0 && _cellX + offset.first < 8 && _cellY + offset.second >= 0 && _cellY + offset.second < 8)
		{
			if (offset.first == 0)
			{
				// Check if there's a piece in front of the pawn
				if (!board->isTherePiece(_cellX, _cellY + offset.second))
				{
					board->getCellAt(_cellX, _cellY + offset.second)->turnOn();
				}
			}
			else
			{
				// Check if there's an enemy in the diagonal cells
				if (board->isThereEnemy(_cellX + offset.first, _cellY + offset.second))
				{
					board->getCellAt(_cellX + offset.first, _cellY + offset.second)->turnOn();
				}
			}
		}
	}
	// Check if it's the pawn's first move
	if ((_cellY == 6 && _color == "white" && !(board->isTherePiece(_cellX, 4))) || (_cellY == 1 && _color == "black" && !(board->isTherePiece(_cellX, 3))))
		board->getCellAt(_cellX, _cellY - 2 * sign)->turnOn();
}
Rook::Rook(int cellX, int cellY, wxBitmap image, std::string id)
	: Piece(cellX, cellY, image, id)
{
}

void Rook::illuminatePaths(Board *board)
{
	// Upward direction
	int x, y;
	for (y = _cellY - 1; y >= 0 && !board->isTherePiece(_cellX, y); y--)
		board->getCellAt(_cellX, y)->turnOn();

	if (y >= 0 && board->isThereEnemy(_cellX, y))
		board->getCellAt(_cellX, y)->turnOn();

	// Downward direction
	for (y = _cellY + 1; y < 8 && !board->isTherePiece(_cellX, y); y++)
		board->getCellAt(_cellX, y)->turnOn();

	if (y < 8 && board->isThereEnemy(_cellX, y))
		board->getCellAt(_cellX, y)->turnOn();

	// Left direction
	for (x = _cellX - 1; x >= 0 && !board->isTherePiece(x, _cellY); x--)
		board->getCellAt(x, _cellY)->turnOn();

	if (x >= 0 && board->isThereEnemy(x, _cellY))
		board->getCellAt(x, _cellY)->turnOn();

	// Right direction
	for (x = _cellX + 1; x < 8 && !board->isTherePiece(x, _cellY); x++)
		board->getCellAt(x, _cellY)->turnOn();

	if (x < 8 && board->isThereEnemy(x, _cellY))
		board->getCellAt(x, _cellY)->turnOn();
}

Knight::Knight(int cellX, int cellY, wxBitmap image, std::string id)
	: Piece(cellX, cellY, image, id)
{
}

void Knight::illuminatePaths(Board *board)
{
	std::pair<int, int> offsets[8] = {{-1, -2}, {-1, 2}, {-2, 1}, {-2, -1}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
	for (auto offset : offsets)
	{
		if (_cellX + offset.first >= 0 && _cellX + offset.first <= 7 && _cellY + offset.second >= 0 && _cellY + offset.second <= 7 && !board->isThereAlly(_cellX + offset.first, _cellY + offset.second))
			board->getCellAt(_cellX + offset.first, _cellY + offset.second)->turnOn();
	}
}

Bishop::Bishop(int cellX, int cellY, wxBitmap image, std::string id)
	: Piece(cellX, cellY, image, id)
{
}

void Bishop::illuminatePaths(Board *board)
{
	// Top-left direction
	int x, y;
	for (x = _cellX - 1, y = _cellY - 1; x >= 0 && y >= 0 && !board->isTherePiece(x, y); x--, y--)
		board->getCellAt(x, y)->turnOn();

	if (x >= 0 && y >= 0 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();

	// Top-right direction
	for (x = _cellX + 1, y = _cellY - 1; x < 8 && y >= 0 && !board->isTherePiece(x, y); x++, y--)
		board->getCellAt(x, y)->turnOn();

	if (x < 8 && y >= 0 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();

	// Bottom-left direction
	for (x = _cellX - 1, y = _cellY + 1; x >= 0 && y < 8 && !board->isTherePiece(x, y); x--, y++)
		board->getCellAt(x, y)->turnOn();

	if (x >= 0 && y < 8 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();

	// Bottom-right direction
	for (x = _cellX + 1, y = _cellY + 1; x < 8 && y < 8 && !board->isTherePiece(x, y); x++, y++)
		board->getCellAt(x, y)->turnOn();

	if (x < 8 && y < 8 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();
}

Queen::Queen(int cellX, int cellY, wxBitmap image, std::string id)
	: Piece(cellX, cellY, image, id)
{
}

void Queen::illuminatePaths(Board *board)
{
	// Top-left direction
	int x, y;
	for (x = _cellX - 1, y = _cellY - 1; x >= 0 && y >= 0 && !board->isTherePiece(x, y); x--, y--)
		board->getCellAt(x, y)->turnOn();

	if (x >= 0 && y >= 0 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();

	// Top-right direction
	for (x = _cellX + 1, y = _cellY - 1; x < 8 && y >= 0 && !board->isTherePiece(x, y); x++, y--)
		board->getCellAt(x, y)->turnOn();

	if (x < 8 && y >= 0 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();

	// Bottom-left direction
	for (x = _cellX - 1, y = _cellY + 1; x >= 0 && y < 8 && !board->isTherePiece(x, y); x--, y++)
		board->getCellAt(x, y)->turnOn();

	if (x >= 0 && y < 8 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();

	// Bottom-right direction
	for (x = _cellX + 1, y = _cellY + 1; x < 8 && y < 8 && !board->isTherePiece(x, y); x++, y++)
		board->getCellAt(x, y)->turnOn();

	if (x < 8 && y < 8 && board->isThereEnemy(x, y))
		board->getCellAt(x, y)->turnOn();

	// Upward direction
	for (y = _cellY - 1; y >= 0 && !board->isTherePiece(_cellX, y); y--)
		board->getCellAt(_cellX, y)->turnOn();

	if (y >= 0 && board->isThereEnemy(_cellX, y))
		board->getCellAt(_cellX, y)->turnOn();

	// Downward direction
	for (y = _cellY + 1; y < 8 && !board->isTherePiece(_cellX, y); y++)
		board->getCellAt(_cellX, y)->turnOn();

	if (y < 8 && board->isThereEnemy(_cellX, y))
		board->getCellAt(_cellX, y)->turnOn();

	// Left direction
	for (x = _cellX - 1; x >= 0 && !board->isTherePiece(x, _cellY); x--)
		board->getCellAt(x, _cellY)->turnOn();

	if (x >= 0 && board->isThereEnemy(x, _cellY))
		board->getCellAt(x, _cellY)->turnOn();

	// Right direction
	for (x = _cellX + 1; x < 8 && !board->isTherePiece(x, _cellY); x++)
		board->getCellAt(x, _cellY)->turnOn();

	if (x < 8 && board->isThereEnemy(x, _cellY))
		board->getCellAt(x, _cellY)->turnOn();
}

King::King(int cellX, int cellY, wxBitmap image, std::string id)
	: Piece(cellX, cellY, image, id)
{
}

void King::illuminatePaths(Board *board)
{
	std::pair<int, int> offsets[8] = {{-1, -1}, {-1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	for (auto offset : offsets)
	{
		if (_cellX + offset.first >= 0 && _cellX + offset.first < 8 && _cellY + offset.second >= 0 && _cellY + offset.second < 8 && !board->isThereAlly(_cellX + offset.first, _cellY + offset.second))
			board->getCellAt(_cellX + offset.first, _cellY + offset.second)->turnOn();
	}
}