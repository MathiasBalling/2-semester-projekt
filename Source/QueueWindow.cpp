#include "../Header/QueueWindow.h"

QueueWindow::QueueWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    // Create the panel
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    // Create the listview
    m_queuelist = new wxListView(panel);

    // Add
    m_queuelist->AppendColumn("ID");
    m_queuelist->AppendColumn("Operation");
    m_queuelist->AppendColumn("X-coordinate");
    m_queuelist->AppendColumn("Y-coordinate");
    m_queuelist->AppendColumn("Z-coordinate");

    int w, h;
    wxDisplaySize(&w, &h);
    w = w - (h - 38 - 30);
    // Set the column width
    m_queuelist->SetColumnWidth(0, w * 0.2);
    m_queuelist->SetColumnWidth(1, w * 0.3);
    m_queuelist->SetColumnWidth(2, w / 6);
    m_queuelist->SetColumnWidth(3, w / 6);
    m_queuelist->SetColumnWidth(4, w / 6);

    wxStaticText *text = new wxStaticText(panel, wxID_ANY, "Moves in queue", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    text->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(text, 0, wxEXPAND | wxALL, 5);
    sizer->Add(m_queuelist, 1, wxEXPAND);

    panel->SetSizer(sizer);
}

void QueueWindow::addItem(const wxString &id, const wxString &op, const int &cellX, const int &cellY, const int &z)
{
    int index = m_queuelist->GetItemCount();
    m_queuelist->InsertItem(index, id);
    m_queuelist->SetItem(index, 1, op);
    m_queuelist->SetItem(index, 2, wxString::Format("%d", cellX));
    m_queuelist->SetItem(index, 3, wxString::Format("%d", cellY));
    m_queuelist->SetItem(index, 4, wxString::Format("%d", z));
}

void QueueWindow::removeFirstItem()
{
    m_queuelist->DeleteItem(0);
}
