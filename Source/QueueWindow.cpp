#include "../Header/QueueWindow.h"

QueueWindow::QueueWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    // Create the panel
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    // Create the listview
    m_list = new wxListView(panel);
    
    // Add 
    m_list->AppendColumn("ID");
    m_list->AppendColumn("Operation");
    m_list->AppendColumn("X-coordinate");
    m_list->AppendColumn("Y-coordinate");
    m_list->AppendColumn("Z-coordinate");

    // Set the column width
    m_list->SetColumnWidth(0, 100);
    m_list->SetColumnWidth(1, 150);
    m_list->SetColumnWidth(2, 250/3);
    m_list->SetColumnWidth(3, 250/3);
    m_list->SetColumnWidth(4, 250/3);

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(m_list, 1, wxEXPAND);

    panel->SetSizerAndFit(sizer);
}

void QueueWindow::addItem(const wxString &id, const wxString &op, const int &cellX, const int &cellY, const int &z)
{
    int index = m_list->GetItemCount();
    m_list->InsertItem(index, id);
    m_list->SetItem(index, 1, op);
    m_list->SetItem(index, 2, wxString::Format("%d", cellX));
    m_list->SetItem(index, 3, wxString::Format("%d", cellY));
    m_list->SetItem(index, 4, wxString::Format("%d", z));
}

void QueueWindow::removeFirstItem()
{
    m_list->DeleteItem(0);
}
