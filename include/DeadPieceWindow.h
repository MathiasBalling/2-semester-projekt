#pragma once

// wxWidgets
#include <wx/listctrl.h>
#include <wx/wx.h>

class DeadPieceWindow : public wxFrame {
public:
  DeadPieceWindow(const wxString &title);
  void addWhite(const wxString &text, const int &cellX, const int &cellY);
  void addBlack(const wxString &text, const int &cellX, const int &cellY);
  void removeFirstWhite();
  void removeFirstBlack();

private:
  wxListView *m_whiteList;
  wxListView *m_blackList;
};
