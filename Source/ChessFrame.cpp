// Header Files
#include "../Header/ChessFrame.h"
#include "../Header/ChessPanel.h"
#include "../Header/Board.h"

ChessFrame::ChessFrame(const wxString &title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 1000))
{
	// Create a logger window
	m_logger = new wxLogWindow(this, "Chess Log", true, false);
	wxLog::SetActiveTarget(m_logger);

	wxImage::AddHandler(new wxPNGHandler());

	// Create the board
	Board *board = new Board();
	m_board = board;

	// Create the panel (graphics)
	ChessPanel *chessPanel = new ChessPanel(this, board);

	// Create the menu
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

ChessFrame::~ChessFrame()
{
	wxLog::SetActiveTarget(nullptr);
	delete m_logger;
	delete m_board;
}