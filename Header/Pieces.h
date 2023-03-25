#pragma once

// wxWidgets
#include <wx/wx.h>

// Header Files
#include "../Header/ChessFrame.h"

class Board;

class Piece
{
public:
	Piece(int x, int y, wxBitmap image, std::string id);
	virtual void illuminatePaths(Board *board) = 0;
	virtual bool canMove(Board *board);
	int getCellX(), getCellY();
	void setCellX(int x), setCellY(int y);
	std::string getId();
	wxBitmap getImage();
	std::string getColor();
	void move(int targetX, int targetY, Board *board);
	bool isAlive();
	void setAlive(bool isAlive);

protected:
	int _cellX, _cellY;
	std::string _id;
	wxBitmap _image;
	std::string _color;
	bool _alive;
};

class Pawn : public Piece
{
public:
	Pawn(int cellX, int cellYy, wxBitmap image, std::string id);
	void illuminatePaths(Board *board) override;
};

class Queen : public Piece
{
public:
	Queen(int cellX, int cellY, wxBitmap image, std::string id);
	void illuminatePaths(Board *board) override;
};

class King : public Piece
{
public:
	King(int cellX, int cellY, wxBitmap image, std::string id);
	void illuminatePaths(Board *board) override;
};

class Bishop : public Piece
{
public:
	Bishop(int cellX, int cellY, wxBitmap image, std::string id);
	void illuminatePaths(Board *board) override;
};

class Knight : public Piece
{
public:
	Knight(int cellX, int cellY, wxBitmap image, std::string id);
	void illuminatePaths(Board *board) override;
};

class Rook : public Piece
{
public:
	Rook(int cellX, int cellY, wxBitmap image, std::string id);
	void illuminatePaths(Board *board) override;
};