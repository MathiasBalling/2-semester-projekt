// Header Files
#include "../Header/ChessPanel.h"

// wxWidgets
#include <wx/dcbuffer.h>

ChessPanel::ChessPanel(wxFrame *parent, Board *board)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE),
	  _board(board), _enemySelected(false)
{
	wxWindow::SetBackgroundStyle(wxBG_STYLE_PAINT);
	Connect(wxEVT_PAINT, wxPaintEventHandler(ChessPanel::OnPaint));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(ChessPanel::OnLeftMouseDown));
}

void ChessPanel::OnPaint(wxPaintEvent &event)
{
	// To avoid flicker
	wxBufferedPaintDC dc(this);
	wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
	clearBuffer(gc);

	// Draw the board and pieces with their current positions and illumination
	drawBoard(gc);
	drawPieces(gc);

	delete gc;
}

void ChessPanel::clearBuffer(wxGraphicsContext *gc)
{
	const wxColor white = wxColor(235, 236, 209);

	gc->SetPen(*wxTRANSPARENT_PEN);
	gc->SetBrush(wxBrush(white));
	gc->DrawRectangle(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight());
}

void ChessPanel::OnLeftMouseDown(wxMouseEvent &event)
{
	// Check if game is finished
	if (_board->isGameFinished())
		return;

	// Get the mouse position
	auto pos = event.GetPosition();

	// Calculate the cell size
	const int cellLenX = GetClientSize().GetWidth() / 8;
	const int cellLenY = GetClientSize().GetHeight() / 8;

	// Translate mouse position to a cell
	int cellX = (int)(pos.x / cellLenX);
	int cellY = (int)(pos.y / cellLenY);

	// Get the selected cell
	Cell *selectedCell = _board->getCellAt(cellX, cellY);

	// Set selected cell if there is ally
	// Or override the selected cell with another ally cell
	if (_board->isThereAlly(cellX, cellY))
	{
		_board->eraseAllIllumination();
		auto piece = selectedCell->getPiece();
		piece->illuminatePaths(_board);
		_board->setSelectedPiece(piece);
		wxPanel::Refresh();
	}
	// Check if selected cell is movable to selected cell
	else if (selectedCell->isIlluminated())
	{
		// Move there
		_board->getSelectedPiece()->move(cellX, cellY, _board);
		_board->eraseAllIllumination();
		_board->setSelectedPiece(nullptr);
		_board->switchTurn();
		wxPanel::Refresh();
	}
	// Clicked on non movable cell
	else
	{
		_board->eraseAllIllumination();
		_board->setSelectedPiece(nullptr);
		wxPanel::Refresh();
	}
}

void ChessPanel::drawBoard(wxGraphicsContext *gc)
{
	const wxColor white = wxColor(235, 236, 209);
	const wxColor black = wxColor(189, 118, 71);
	const wxColor grey = wxColor(80, 80, 80, 150);
	const wxColor yellow = wxColor(255, 255, 0, 100);
	gc->SetPen(*wxTRANSPARENT_PEN);

	const int cellLenX = GetClientSize().GetWidth() / 8;
	const int cellLenY = GetClientSize().GetHeight() / 8;

	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 8; x++)
		{
			if ((x + y) % 2 == 0)
				gc->SetBrush(wxBrush(white));
			else
				gc->SetBrush(wxBrush(black));
			gc->DrawRectangle(x * cellLenX, y * cellLenY, cellLenX, cellLenY);
			if (_board->getCellAt(x, y)->isIlluminated())
			{
				gc->SetBrush(wxBrush(grey));
				gc->DrawEllipse(x * cellLenX + cellLenX / 4, y * cellLenY + cellLenY / 4, cellLenX / 2, cellLenY / 2);
			}
			if (_board->getSelectedPiece() == _board->getCellAt(x, y)->getPiece() && _board->getSelectedPiece())
			{
				gc->SetBrush(wxBrush(yellow));
				gc->DrawRectangle(x * cellLenX, y * cellLenY, cellLenX, cellLenY);
			}
		}
}

void ChessPanel::drawPieces(wxGraphicsContext *gc)
{
	const int cellLenX = GetClientSize().GetWidth() / 8;
	const int cellLenY = GetClientSize().GetHeight() / 8;
	auto piecesMap = _board->getPiecesMap();

	for (auto &it : piecesMap)
	{
		Piece *piece = it.second;
		if (piece->isAlive())
		{
			const int cellPosX = piece->getCellX() * cellLenX + (cellLenX / 2 - (piece->getImage().GetWidth()) / 2);
			const int cellPosY = piece->getCellY() * cellLenY + (cellLenY / 2 - (piece->getImage().GetHeight()) / 2);
			const int imageSizeX = piece->getImage().GetWidth();
			const int imageSizeY = piece->getImage().GetHeight();
			gc->DrawBitmap(piece->getImage(), cellPosX, cellPosY, imageSizeX, imageSizeY);
		}
	}
}