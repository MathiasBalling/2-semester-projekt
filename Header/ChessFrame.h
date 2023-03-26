#pragma once

// wxWidgets
#include <wx/wx.h>

class Board;

class ChessFrame : public wxFrame
{
public:
	ChessFrame(const wxString &title);
	~ChessFrame();

private:
	void OnAbout(wxCommandEvent &event);
	wxLog *_logger;
	Board *_board;
};
