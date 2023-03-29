// Header Files
#include "../Header/main.h"
#include "../Header/ChessFrame.h"

IMPLEMENT_APP(ChessApp)

bool ChessApp::OnInit()
{
	int w, h;
	wxDisplaySize(&w, &h);
	h = h - 38 - 30;
	ChessFrame *chessFrame = new ChessFrame(wxT("NBNP - Chess"));
	chessFrame->SetClientSize(wxSize(h, h));
	chessFrame->SetMinClientSize(wxSize(h, h));
	chessFrame->SetMaxClientSize(wxSize(h, h));
	chessFrame->SetPosition(wxPoint(w - h, 38));
	chessFrame->Show(true);

	return true;
}