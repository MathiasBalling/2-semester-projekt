#pragma once

// Header Files
#include "Board.h"
#include "Piece.h"

// wxWidgets
#include <wx/wx.h>
#include <wx/graphics.h>

class ChessPanel : public wxPanel
{
public:
	ChessPanel(wxFrame *parent, Board *board);

private:
	void OnPaint(wxPaintEvent &event);
	void OnLeftMouseDown(wxMouseEvent &event);
	void clearBuffer(wxGraphicsContext *gc);
	void drawBoard(wxGraphicsContext *gc);
	void drawPieces(wxGraphicsContext *gc);
	Board *m_board;
	bool m_enemySelected;
};