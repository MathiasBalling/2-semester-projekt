#pragma once

// wxWidgets
#include <wx/wx.h>
#include <wx/listctrl.h>

class QueueWindow : public wxFrame
{
public:
    QueueWindow(const wxString &title);
    void addItem(const wxString &text, const wxString &op, const int &cellX, const int &cellY, const int &z);
    void removeFirstItem();

private:
    wxListView *m_list;
};
