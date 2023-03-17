#include "../Header/ChessFrame.h"
#include "../Header/ChessPanel.h"
#include "../Header/Board.h"

ChessFrame::ChessFrame(const wxString &title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 1000))
{
	Centre();
	wxImage::AddHandler(new wxPNGHandler());
	Board *board = new Board();
	ChessPanel *chessPanel = new ChessPanel(this, board);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);

	Bind(wxEVT_MENU, &ChessFrame::OnAbout, this, wxID_ABOUT);
}
void ChessFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageBox("This is a chess app connected to a UR5 robot.\nMade by No Bitches No Problem",
				 "About NBNP - Chess", wxOK | wxICON_INFORMATION);
}