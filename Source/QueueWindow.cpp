#include "../Header/QueueWindow.h"

QueueWindow::QueueWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    // Create the panel
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    // Create the listview
    _list = new wxListView(panel);
    
    // Add 
    _list->AppendColumn("ID");
    _list->AppendColumn("Operation");
    _list->AppendColumn("X-coordinate");
    _list->AppendColumn("Y-coordinate");
    _list->AppendColumn("Z-coordinate");

    // Set the column width
    _list->SetColumnWidth(0, 100);
    _list->SetColumnWidth(1, 150);
    _list->SetColumnWidth(2, 250/3);
    _list->SetColumnWidth(3, 250/3);
    _list->SetColumnWidth(4, 250/3);

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(_list, 1, wxEXPAND);

    panel->SetSizerAndFit(sizer);
}

void QueueWindow::addItem(const wxString &id, const wxString &op, const int &cellX, const int &cellY, const int &z)
{
    int index = _list->GetItemCount();
    _list->InsertItem(index, id);
    _list->SetItem(index, 1, op);
    _list->SetItem(index, 2, wxString::Format("%d", cellX));
    _list->SetItem(index, 3, wxString::Format("%d", cellY));
    _list->SetItem(index, 4, wxString::Format("%d", z));
}

void QueueWindow::removeFirstItem()
{
    _list->DeleteItem(0);
}
