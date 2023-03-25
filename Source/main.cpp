// Header Files
#include "../Header/main.h"
#include "../Header/ChessFrame.h"

IMPLEMENT_APP(ChessApp)

bool ChessApp::OnInit()
{
	ChessFrame *chessFrame = new ChessFrame(wxT("NBNP - Chess"));
	chessFrame->SetClientSize(wxSize(1000, 1000));
	chessFrame->SetMinClientSize(wxSize(1000, 1000));
	chessFrame->SetMaxClientSize(wxSize(1000, 1000));
	chessFrame->Center();
	chessFrame->Show(true);

	return true;
}