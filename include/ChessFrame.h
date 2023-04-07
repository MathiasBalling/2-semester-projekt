#pragma once

// wxWidgets
#include <wx/wx.h>

class Board;

class ChessFrame : public wxFrame {
public:
  ChessFrame(const wxString &title);
  ~ChessFrame();

private:
  void OnAbout(wxCommandEvent &event);
  wxLog *m_logger;
  Board *m_board;
};
