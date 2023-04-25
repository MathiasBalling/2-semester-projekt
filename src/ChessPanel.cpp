// Header Files
#include "ChessPanel.h"

// wxWidgets
#include <wx/dcbuffer.h>

ChessPanel::ChessPanel(wxFrame *parent, Board *board)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize,
              wxBORDER_NONE),
      m_board(board), m_enemySelected(false) {
  wxWindow::SetBackgroundStyle(wxBG_STYLE_PAINT);
  Bind(wxEVT_PAINT, &ChessPanel::OnPaint, this);
  Bind(wxEVT_LEFT_DOWN, &ChessPanel::OnLeftMouseDown, this);
}

void ChessPanel::OnPaint(wxPaintEvent &event) {
  // To avoid flicker
  wxBufferedPaintDC dc(this);
  wxGraphicsContext *gc = wxGraphicsContext::Create(dc);
  clearBuffer(gc);

  // Draw the board and pieces with their current positions and illumination
  drawBoard(gc);
  drawPieces(gc);

  delete gc;
}

void ChessPanel::clearBuffer(wxGraphicsContext *gc) {
  const wxColor light = wxColor(235, 236, 209);

  gc->SetPen(*wxTRANSPARENT_PEN);
  gc->SetBrush(wxBrush(light));
  gc->DrawRectangle(0, 0, GetClientSize().GetWidth(),
                    GetClientSize().GetHeight());
}

void ChessPanel::OnLeftMouseDown(wxMouseEvent &event) {
  // Check if game is finished
  if (m_board->isGameFinished())
    return;

  // Get the mouse position
  auto pos = event.GetPosition();

  // Calculate the cell size
  const int cellLenX = GetClientSize().GetWidth() / 8;
  const int cellLenY = GetClientSize().GetHeight() / 8;

  // Translate mouse position to a cell
  int cellX = (int)(pos.x / cellLenX);
  int cellY = (int)(pos.y / cellLenY);
  cellX = cellX == 8 ? 7 : cellX;
  cellY = cellY == 8 ? 7 : cellY;

  // Get the selected cell
  Cell *selectedCell = m_board->getCellAt(cellX, cellY);

  // Set selected cell if there is ally
  // Or override the selected cell with another ally cell
  if (m_board->isThereAlly(cellX, cellY)) {
    m_board->eraseAllIllumination();
    auto piece = selectedCell->getPiece();
    piece->illuminatePaths(m_board);
    m_board->setSelectedPiece(piece);
    wxPanel::Refresh();
  }
  // Check if selected cell is movable to selected cell
  else if (selectedCell->isIlluminated()) {
    // Move there
    m_board->getSelectedPiece()->move(cellX, cellY, m_board);
    m_board->eraseAllIllumination();
    m_board->setSelectedPiece(nullptr);
    m_board->switchTurn();
    wxPanel::Refresh();
  }
  // Clicked on non movable cell
  else {
    m_board->eraseAllIllumination();
    m_board->setSelectedPiece(nullptr);
    wxPanel::Refresh();
  }
}

void ChessPanel::drawBoard(wxGraphicsContext *gc) {
  const wxColor light = wxColor(235, 236, 209);
  const wxColor dark = wxColor(189, 118, 71);
  const wxColor grey = wxColor(80, 80, 80, 150);
  const wxColor yellow = wxColor(255, 255, 0, 100);
  gc->SetPen(*wxTRANSPARENT_PEN);

  const int cellLenX = GetClientSize().GetWidth() / 8;
  const int cellLenY = GetClientSize().GetHeight() / 8;

  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 8; x++) {
      if ((x + y) % 2 == 0)
        gc->SetBrush(wxBrush(light));
      else
        gc->SetBrush(wxBrush(dark));
      gc->DrawRectangle(x * cellLenX, y * cellLenY, cellLenX, cellLenY);
      if (m_board->getCellAt(x, y)->isIlluminated()) {
        if (m_board->isThereEnemy(x, y)) {
          gc->SetPen(wxPen(*wxWHITE, 6));
          gc->SetBrush(*wxTRANSPARENT_BRUSH);
          gc->DrawRectangle(x * cellLenX + 3, y * cellLenY + 3, cellLenX - 6,
                            cellLenY - 6);
          gc->SetPen(*wxTRANSPARENT_PEN);
        } else {
          gc->SetBrush(wxBrush(grey));
          gc->DrawEllipse(x * cellLenX + cellLenX * 0.25,
                          y * cellLenY + cellLenY * 0.25, cellLenX * 0.5,
                          cellLenY * 0.5);
        }
      }

      if (m_board->getSelectedPiece() == m_board->getCellAt(x, y)->getPiece() &&
          m_board->getSelectedPiece()) {
        gc->SetBrush(wxBrush(yellow));
        gc->DrawRectangle(x * cellLenX, y * cellLenY, cellLenX, cellLenY);
      }
    }
}

void ChessPanel::drawPieces(wxGraphicsContext *gc) {
  const int cellLenX = GetClientSize().GetWidth() / 8;
  const int cellLenY = GetClientSize().GetHeight() / 8;
  auto piecesMap = m_board->getPiecesMap();

  for (auto &it : piecesMap) {
    Piece *piece = it.second;
    if (piece->isAlive()) {
      int dim = cellLenX < cellLenY ? cellLenX : cellLenY;
      float scale = 0.8;
      int imgHeight = piece->getImage().GetHeight();
      int imgWidth = piece->getImage().GetWidth();

      if (imgHeight > imgWidth) {
        imgWidth = (int)(imgWidth * (dim * scale) / imgHeight);
        imgHeight = (int)(dim * scale);
      } else {
        imgHeight = (int)(imgHeight * (dim * scale) / imgWidth);
        imgWidth = (int)(dim * scale);
      }
      int cellPosX =
          piece->getCellX() * cellLenX + (cellLenX / 2 - imgWidth / 2);
      int cellPosY =
          piece->getCellY() * cellLenY + (cellLenY / 2 - imgHeight / 2);
      int imageSizeX = imgWidth;
      int imageSizeY = imgHeight;
      gc->DrawBitmap(piece->getImage(), cellPosX, cellPosY, imageSizeX,
                     imageSizeY);
    }
  }
}