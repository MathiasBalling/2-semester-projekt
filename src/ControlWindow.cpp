#include "ControlWindow.h"

ControlWindow::ControlWindow(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize) {

  // Get display size
  int w, h;
  wxDisplaySize(&w, &h);
  w = w - (h - 38 - 30);

  // Create the mainpanel
  wxPanel *mainpanel = new wxPanel(this, wxID_ANY);

  // Create the queuepanel
  wxPanel *queuepanel = new wxPanel(mainpanel, wxID_ANY);

  // Create the queuelistview
  m_queuelist = new wxListView(queuepanel);

  // Add queuecolumns
  m_queuelist->AppendColumn("ID");
  m_queuelist->AppendColumn("Operation");
  m_queuelist->AppendColumn("X-coordinate");
  m_queuelist->AppendColumn("Y-coordinate");
  m_queuelist->AppendColumn("Z-coordinate");
  // Set the column width
  m_queuelist->SetColumnWidth(0, w * 0.2);
  m_queuelist->SetColumnWidth(1, w * 0.3);
  m_queuelist->SetColumnWidth(2, w / 6);
  m_queuelist->SetColumnWidth(3, w / 6);
  m_queuelist->SetColumnWidth(4, w / 6);

  // Add header text
  wxStaticText *queueText = new wxStaticText(
      queuepanel, wxID_ANY, "Moves in queue", wxDefaultPosition, wxDefaultSize,
      wxALIGN_CENTRE_HORIZONTAL);
  queueText->SetFont(
      wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

  // Add sizer for queuepanel
  wxBoxSizer *queuesizer = new wxBoxSizer(wxVERTICAL);
  queuesizer->Add(queueText, 0, wxEXPAND | wxALL, 5);
  queuesizer->Add(m_queuelist, 1, wxEXPAND);
  queuepanel->SetSizer(queuesizer);

  wxPanel *bottompanel = new wxPanel(mainpanel, wxID_ANY);
  w /= 2;
  wxPanel *whitePanel =
      new wxPanel(bottompanel, wxID_ANY, wxDefaultPosition, wxSize(w, -1));

  // Create the listview
  m_whitelist = new wxListView(whitePanel);
  // Add columns
  m_whitelist->AppendColumn("ID");
  m_whitelist->AppendColumn("x");
  m_whitelist->AppendColumn("y");
  // Set the column width
  m_whitelist->SetColumnWidth(0, w * 0.5);
  m_whitelist->SetColumnWidth(1, w * 0.25);
  m_whitelist->SetColumnWidth(2, w * 0.25 + 1);
  // Header text
  wxStaticText *whiteDeadtext = new wxStaticText(
      whitePanel, wxID_ANY, "White dead pieces", wxDefaultPosition,
      wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
  whiteDeadtext->SetFont(
      wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  // Create the sizer for white
  wxBoxSizer *whitesizer = new wxBoxSizer(wxVERTICAL);
  whitesizer->Add(whiteDeadtext, 0, wxEXPAND | wxALL, 5);
  whitesizer->Add(m_whitelist, 1, wxEXPAND);
  whitePanel->SetSizer(whitesizer);

  // Create the panel for black
  wxPanel *blackPanel =
      new wxPanel(bottompanel, wxID_ANY, wxDefaultPosition, wxSize(w, -1));
  // Create the listview
  m_blacklist = new wxListView(blackPanel);
  // Add columns
  m_blacklist->AppendColumn("ID");
  m_blacklist->AppendColumn("x");
  m_blacklist->AppendColumn("y");
  // Set the column width
  m_blacklist->SetColumnWidth(0, w * 0.5);
  m_blacklist->SetColumnWidth(1, w * 0.25);
  m_blacklist->SetColumnWidth(2, w * 0.25 + 1);
  // Header text
  wxStaticText *blackDeadtext = new wxStaticText(
      blackPanel, wxID_ANY, "Black dead pieces", wxDefaultPosition,
      wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
  blackDeadtext->SetFont(
      wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  // Create the sizer for black
  wxBoxSizer *blacksizer = new wxBoxSizer(wxVERTICAL);
  blacksizer->Add(blackDeadtext, 0, wxEXPAND | wxALL, 5);
  blacksizer->Add(m_blacklist, 1, wxEXPAND);
  blackPanel->SetSizer(blacksizer);

  // Create the sizer for the whole window
  wxBoxSizer *bottomsizer = new wxBoxSizer(wxHORIZONTAL);
  bottomsizer->Add(whitePanel, 1, wxEXPAND);
  bottomsizer->Add(blackPanel, 1, wxEXPAND);
  bottompanel->SetSizer(bottomsizer);

  wxBoxSizer *mainsizer = new wxBoxSizer(wxVERTICAL);
  mainsizer->Add(queuepanel, 6, wxEXPAND);
  mainsizer->Add(bottompanel,4, wxEXPAND);
  mainpanel->SetSizer(mainsizer);
}

void ControlWindow::addItem(const wxString &id, const wxString &op,
                            const int &cellX, const int &cellY, const int &z) {
  // Add moves to queue
  int index = m_queuelist->GetItemCount();
  m_queuelist->InsertItem(index, id);
  m_queuelist->SetItem(index, 1, op);
  m_queuelist->SetItem(index, 2, wxString::Format("%d", cellX));
  m_queuelist->SetItem(index, 3, wxString::Format("%d", cellY));
  m_queuelist->SetItem(index, 4, wxString::Format("%d", z));
}

void ControlWindow::removeFirstItem() { m_queuelist->DeleteItem(0); }

void ControlWindow::addWhite(const wxString &id, const int &cellX,
                             const int &cellY) {
  int index = m_whitelist->GetItemCount();
  m_whitelist->InsertItem(index, id);
  m_whitelist->SetItem(index, 1, wxString::Format("%d", cellX));
  m_whitelist->SetItem(index, 2, wxString::Format("%d", cellY));
}

void ControlWindow::addBlack(const wxString &id, const int &cellX,
                             const int &cellY) {
  int index = m_blacklist->GetItemCount();
  m_blacklist->InsertItem(index, id);
  m_blacklist->SetItem(index, 1, wxString::Format("%d", cellX));
  m_blacklist->SetItem(index, 2, wxString::Format("%d", cellY));
}

void ControlWindow::removeFirstWhite() { m_whitelist->DeleteItem(0); }

void ControlWindow::removeFirstBlack() { m_blacklist->DeleteItem(0); }
