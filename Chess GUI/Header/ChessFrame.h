#pragma once
#include <wx/wx.h>

class ChessFrame : public wxFrame
{
public:
	ChessFrame(const wxString &title);

private:
	void OnAbout(wxCommandEvent &event);
};
