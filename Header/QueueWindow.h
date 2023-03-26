#pragma once

// wxWidgets
#include <wx/wx.h>

class QueueWindow : public wxFrame
{
public:
    QueueWindow(const wxString &title);

private:
    void OnClick(wxCommandEvent &event);
};
