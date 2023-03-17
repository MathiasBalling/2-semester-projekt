#include "../Header/ChessPanel.h"
#include <wx/dcbuffer.h>

ChessPanel::ChessPanel(wxFrame *parent, Board *board)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE),
	  board{board}, enemySelected{false}
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
	drawBoard(gc);
	drawPieces(gc);

	delete gc;
}

void ChessPanel::clearBuffer(wxGraphicsContext *gc)
{
	const wxColor white = wxColor(235, 236, 209);
	;
	gc->SetPen(*wxTRANSPARENT_PEN);
	gc->SetBrush(wxBrush(white));
	gc->DrawRectangle(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight());
}

void ChessPanel::OnLeftMouseDown(wxMouseEvent &event)
{
	if (board->isGameFinished())
		return;
	auto pos = event.GetPosition();
	const int cellLenX = GetClientSize().GetWidth() / 8;
	const int cellLenY = GetClientSize().GetHeight() / 8;
	// Translate pixels coords to cells
	int cellX = (int)(pos.x / cellLenX);
	int cellY = (int)(pos.y / cellLenY);

	Cell *selectedCell = board->getCellAt(cellX, cellY);
	// Check if selectedCell is mover's piece
	if (board->isThereAlly(cellX, cellY))
	{
		board->eraseAllIllumination();
		auto piece = selectedCell->getPiece();
		piece->illuminatePaths(board);
		board->setSelectedPiece(piece);
		wxPanel::Refresh();
	}
	else if (selectedCell->isIlluminated())
	{
		// Move there
		board->getSelectedPiece()->move(cellX, cellY, board);
		board->eraseAllIllumination();
		board->setSelectedPiece(nullptr);
		board->switchTurn();
		wxPanel::Refresh();
	}
	// Clicked on empty, non-illuminated cell
	else
	{
		board->eraseAllIllumination();
		board->setSelectedPiece(nullptr);
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
			if (board->getCellAt(x, y)->isIlluminated())
			{
				gc->SetBrush(wxBrush(grey));
				gc->DrawEllipse(x * cellLenX + cellLenX / 4, y * cellLenY + cellLenY / 4, cellLenX / 2, cellLenY / 2);
			}
			if (board->getSelectedPiece() == board->getCellAt(x, y)->getPiece() && board->getSelectedPiece())
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
	auto piecesMap = board->getPiecesMap();
	std::string a = "Begin";
	for (auto &it : piecesMap)
	{
		Piece *piece = it.second;
		if (piece->isAlive())
		{
			const int cellPosX = piece->getCellX() * cellLenX + (cellLenX / 2 - (piece->getImage().GetWidth()) / 2);
			const int cellPosY = piece->getCellY() * cellLenY + (cellLenY / 2 - (piece->getImage().GetHeight()) / 2);
			const int imageSizeX = piece->getImage().GetWidth();
			const int imageSizeY = piece->getImage().GetHeight();
			gc->DrawBitmap(piece->getImage(), cellPosX, cellPosY, imageSizeX, piece->getImage().GetHeight());
		}
	}
}