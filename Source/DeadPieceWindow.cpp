#include "../Header/DeadPieceWindow.h"

DeadPieceWindow::DeadPieceWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    int w, h;
    wxDisplaySize(&w, &h);
    w = (w - 1000) / 2;
    // Create the panel for white
    wxPanel *whitePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(w, -1));
    // Create the listview
    m_whiteList = new wxListView(whitePanel);
    // Add columns
    m_whiteList->AppendColumn("ID");
    m_whiteList->AppendColumn("x");
    m_whiteList->AppendColumn("y");
    // Set the column width
    m_whiteList->SetColumnWidth(0, w * 0.5);
    m_whiteList->SetColumnWidth(1, w * 0.25);
    m_whiteList->SetColumnWidth(2, w * 0.25);
    // Header text
    wxStaticText *whiteDead = new wxStaticText(whitePanel, wxID_ANY, "White dead pieces", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    whiteDead->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    // Create the sizer for white
    wxBoxSizer *whitesizer = new wxBoxSizer(wxVERTICAL);
    whitesizer->Add(whiteDead, 0, wxEXPAND | wxALL, 5);
    whitesizer->Add(m_whiteList, 1, wxEXPAND);
    whitePanel->SetSizer(whitesizer);

    // Create the panel for black
    wxPanel *blackPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(w, -1));
    // Create the listview
    m_blackList = new wxListView(blackPanel);
    // Add columns
    m_blackList->AppendColumn("ID");
    m_blackList->AppendColumn("x");
    m_blackList->AppendColumn("y");
    // Set the column width
    m_blackList->SetColumnWidth(0, w * 0.5);
    m_blackList->SetColumnWidth(1, w * 0.25);
    m_blackList->SetColumnWidth(2, w * 0.25);
    // Header text
    wxStaticText *blackDead = new wxStaticText(blackPanel, wxID_ANY, "Black dead pieces", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    blackDead->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    // Create the sizer for black
    wxBoxSizer *blacksizer = new wxBoxSizer(wxVERTICAL);
    blacksizer->Add(blackDead, 0, wxEXPAND | wxALL, 5);
    blacksizer->Add(m_blackList, 1, wxEXPAND);
    blackPanel->SetSizer(blacksizer);

    // Create the sizer for the whole window
    wxBoxSizer *mainsizer = new wxBoxSizer(wxHORIZONTAL);
    mainsizer->Add(whitePanel, 1, wxEXPAND);
    mainsizer->Add(blackPanel, 1, wxEXPAND);
    SetSizerAndFit(mainsizer);
}

void DeadPieceWindow::addWhite(const wxString &id, const int &cellX, const int &cellY)
{
    int index = m_whiteList->GetItemCount();
    m_whiteList->InsertItem(index, id);
    m_whiteList->SetItem(index, 1, wxString::Format("%d", cellX));
    m_whiteList->SetItem(index, 2, wxString::Format("%d", cellY));
}

void DeadPieceWindow::addBlack(const wxString &id, const int &cellX, const int &cellY)
{
    int index = m_blackList->GetItemCount();
    m_blackList->InsertItem(index, id);
    m_blackList->SetItem(index, 1, wxString::Format("%d", cellX));
    m_blackList->SetItem(index, 2, wxString::Format("%d", cellY));
}

void DeadPieceWindow::removeFirstWhite()
{
    m_whiteList->DeleteItem(0);
}

void DeadPieceWindow::removeFirstBlack()
{
    m_blackList->DeleteItem(0);
}
