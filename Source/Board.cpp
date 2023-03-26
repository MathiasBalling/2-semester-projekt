// Header Files
#include "../Header/Board.h"
#include "../Header/Pieces.h"
#include "../Header/AI.h"

// wxWidgets
#include <wx/msgdlg.h>
#include <wx/bitmap.h>

Board::Board()
	: _turn{"white"}, _gameFinished{false}
{
	// Initialize the pieces and cells
	initPieces();
	initCells();
}

Board::~Board()
{
	delete mb;
}

const std::unordered_map<std::string, Piece *> &Board::getPiecesMap()
{
	return _pieces;
}

Piece *Board::getPieceAt(int cellX, int cellY)
{
	return _cells[cellX][cellY]->getPiece();
}

Piece *Board::getSelectedPiece()
{
	return _selectedPiece;
}

void Board::setSelectedPiece(Piece *piece)
{
	_selectedPiece = piece;
}

Cell *Board::getCellAt(int cellX, int cellY)
{
	return _cells[cellX][cellY];
}

std::string Board::getTurn()
{
	return _turn;
}

void Board::switchTurn()
{
	// If the game is finished, don't switch the turn
	if (_gameFinished)
		return;

	// Switch the turn
	_turn = _turn == "white" ? "black" : "white";

	// If the enemy is an AI, let it play
	if (_turn == "black" && _enemyIsAI)
	{
		AI::playTurn(this);
	}
}

void Board::setGameFinished(bool gameFinished)
{
	this->_gameFinished = gameFinished;
	wxMessageBox(wxString("Game ended, " + _turn + " wins."));
}

bool Board::isGameFinished()
{
	return _gameFinished;
}

void Board::eraseAllIllumination()
{
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			getCellAt(x, y)->turnOff();
}

void Board::setEnemyIsAI(bool enemyIsAI)
{
	this->_enemyIsAI = enemyIsAI;
}

bool Board::isThereEnemy(int cellX, int cellY)
{

	return _cells[cellX][cellY]->getPiece() != nullptr && _cells[cellX][cellY]->getPiece()->getColor() != _turn;
}

bool Board::isThereAlly(int cellX, int cellY)
{
	return _cells[cellX][cellY]->getPiece() != nullptr && _cells[cellX][cellY]->getPiece()->getColor() == _turn;
}

bool Board::isTherePiece(int cellX, int cellY)
{
	return _cells[cellX][cellY]->hasPiece();
}

void Board::initPieces()
{
	// Initialize black pawns
	for (int x = 0; x < 8; x++)
	{
		wxImage image("../images/black_pawn.png");									  // Load the image of the black pawn
		Piece *pawn = new Pawn(x, 1, wxBitmap(image), "B_Pawn_" + std::to_string(x)); // Create the black pawns
		_pieces[pawn->getId()] = pawn;												  // Add the pawn to the map
	}
	// Inititialize white pawns
	for (int x = 0; x < 8; x++)
	{
		wxImage image("../images/white_pawn.png");									  // Load the image of the white pawn
		Piece *pawn = new Pawn(x, 6, wxBitmap(image), "W_Pawn_" + std::to_string(x)); // Create the white pawns
		_pieces[pawn->getId()] = pawn;												  // Add the pawn to the map
	}
	// Initialize the other pieces
	std::string ids[] = {"Rook_0", "Knight_0", "Bishop_0", "Queen", "King", "Bishop_1", "Knight_1", "Rook_1"};
	std::string colors[] = {"W", "B"};
	for (int x = 0; x < 8; x++) // Loop through the ids
	{
		for (auto &color : colors) // Loop through the colors
		{
			Piece *piece;
			std::string imageName = color == "W" ? "white" : "black"; // Set start of the image name
			switch (ids[x][0])
			{
			case 'R':					  // If the id starts with R, it's a rook
				imageName += "_rook.png"; // Set the image name
				piece = new Rook(x, color == "W" ? 7 : 0, wxBitmap(wxImage("../images/" + imageName)), color + "_" + ids[x]);
				break;
			case 'K': // If the id starts with K, it's a knight or a king
				if (ids[x][1] == 'i')
				{
					imageName += "_king.png"; // Set the image name
					piece = new King(x, color == "W" ? 7 : 0, wxBitmap(wxImage("../images/" + imageName)), color + "_" + ids[x]);
				}
				else
				{
					imageName += "_knight.png"; // Set the image name
					piece = new Knight(x, color == "W" ? 7 : 0, wxBitmap(wxImage("../images/" + imageName)), color + "_" + ids[x]);
				}
				break;
			case 'B':						// If the id starts with B, it's a bishop
				imageName += "_bishop.png"; // Set the image name
				piece = new Bishop(x, color == "W" ? 7 : 0, wxBitmap(wxImage("../images/" + imageName)), color + "_" + ids[x]);
				break;
			case 'Q':					   // If the id starts with Q, it's a queen
				imageName += "_queen.png"; // Set the image name
				piece = new Queen(x, color == "W" ? 7 : 0, wxBitmap(wxImage("../images/" + imageName)), color + "_" + ids[x]);
			}
			_pieces[piece->getId()] = piece;
		}
	}
}

void Board::initCells()
{
	std::vector<Cell *> empty(8);
	// Make vector of empty cells
	for (int i = 0; i < 8; i++)
	{
		_cells.push_back(empty);
		for (int j = 0; j < 8; j++)
			_cells[i][j] = new Cell();
	}

	// Add the pieces to the cells
	for (auto &it : _pieces)
	{
		Piece *piece = it.second;
		int x = piece->getCellX();
		int y = piece->getCellY();
		_cells[x][y] = new Cell();
		_cells[x][y]->setPiece(piece);
	}
}
