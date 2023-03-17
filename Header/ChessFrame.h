#pragma once
#include <wx/wx.h>

class ChessFrame : public wxFrame
{
public:
	ChessFrame(const wxString &title);
	~ChessFrame();

private:
	void OnAbout(wxCommandEvent &event);
	wxLog *logger;
};
