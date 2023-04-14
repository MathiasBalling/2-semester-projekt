#pragma once

// wxWidgets
#include <wx/listctrl.h>
#include <wx/wx.h>

class ControlWindow : public wxFrame {
public:
  ControlWindow(const wxString &title);
  void addItem(const wxString &text, const wxString &op, const int &cellX,
               const int &cellY, const int &z);
  void removeFirstItem();

  void addWhite(const wxString &text, const int &cellX, const int &cellY);
  void addBlack(const wxString &text, const int &cellX, const int &cellY);
  void removeFirstWhite();
  void removeFirstBlack();

private:
  wxListView *m_queuelist;
  wxListView *m_whitelist;
  wxListView *m_blacklist;
};
