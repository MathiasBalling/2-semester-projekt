#include "../Header/QueueWindow.h"

QueueWindow::QueueWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    // Create the panel
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    // Create the button
    wxButton *button = new wxButton(panel, wxID_ANY, "Hello World", wxPoint(25, 25));

    // Bind the button to the OnClick function
    button->Bind(wxEVT_BUTTON, &QueueWindow::OnClick, this);
}

void QueueWindow::OnClick(wxCommandEvent &event)
{
    wxMessageBox("Hello World", "Hello World", wxOK | wxICON_INFORMATION);
}