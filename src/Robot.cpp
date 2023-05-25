// Header Files
#include "Robot.h"
#include "Board.h"
#include "modbus.h"
#include <_types/_uint8_t.h>
#include <chrono>
#include <string>
#include <thread>

Robot::Robot(Board *board) : m_board(board) {

  // Add the ip address of the modbus device
  m_mb = modbus_new_tcp("192.168.100.11", 502);
  m_serial.openDevice("/dev/tty.usbserial-DK0AID5R", 4800);

  // Connect to the modbus device
  if (modbus_connect(m_mb) == -1) {
    m_connected = false;
    wxLogMessage("Modbus: Connection Failed!");
  }
  if (!m_serial.isDeviceOpen()) {
    m_connected = false;
    wxLogMessage("Serial: Connection Failed!");
  }
  if (m_connected) {
    wxLogMessage("Modbus: Connection Successful!");
    wxLogMessage("Serial: Connection Successful!");
    uint8_t buffer[1] = {2};
    m_serial.writeBytes(buffer, 1);
    m_serial.flushReceiver();
    // Start a worker thread to move pieces from the queue
    m_thread = std::thread(&Robot::movePiece, this);
  }
  // Create a new window to display the queue
  int w, h;
  wxDisplaySize(&w, &h);
  w = w - (h - 38 - 30);
  h = h - 38;
  m_controlWindow = new ControlWindow(wxT("Control Window"));
  m_controlWindow->SetSize(wxSize(w, h));
  m_controlWindow->SetPosition(wxPoint(0, 38));
  m_controlWindow->Show(true);

  makeDialog();
}

Robot::~Robot() {
  // Disconnect from the modbus device
  modbus_free(m_mb);

  // Stop the worker thread
  m_connected = false;

  // Close the queue window
  delete m_controlWindow;
}

void Robot::setXval(int val) {
  if (val < 0) {
    val = val * -1 + 2000;
  }
  modbus_connect(m_mb);
  // Write the x position to the modbus device
  int msg = modbus_write_register(m_mb, 128, val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set x!");
  }
  modbus_close(m_mb);
}

void Robot::setYval(int val) {
  if (val < 0) {
    val = val * -1 + 2000;
  }
  modbus_connect(m_mb);
  // Write the y position to the modbus device
  int msg = modbus_write_register(m_mb, 129, val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set y!");
  }
  modbus_close(m_mb);
}

void Robot::setZval(int val) {
  if (val < 0) {
    val = val * -1 + 2000;
  }
  modbus_connect(m_mb);
  // Write the z position to the modbus device
  int msg = modbus_write_register(m_mb, 130, val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set z!");
  }
  modbus_close(m_mb);
}

void Robot::setCO() {
  modbus_connect(m_mb);
  // Write the configurable output to the modbus device
  int msg = modbus_write_register(m_mb, 31, 1);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set Digital Output!");
  }
  modbus_close(m_mb);
}

int Robot::getDO() {
  modbus_connect(m_mb);
  // Read the digital output from the modbus device
  uint16_t val;
  int msg = modbus_read_registers(m_mb, 1, 1, &val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't get Digital Output!");
    modbus_close(m_mb);
    return -1;
  } else {
    modbus_close(m_mb);
    return val;
  }
}

bool Robot::isConnected() { return m_connected; }

void Robot::movePiece() {
  // To stop the thread for a specific amount of time
  using namespace std::chrono_literals;
  using namespace std::this_thread;
  uint8_t val = 0;
  bool grip = true;
  m_serial.openDevice("/dev/tty.usbserial-DK0AID5R", 4800);
  m_serial.flushReceiver();
  modbus_connect(m_mb);
  while (m_connected) {
    if (shouldRun()) {
      // Get piece position from queue
      int x = m_piecePosQueue[0];
      int y = m_piecePosQueue[1];
      int z = m_piecePosQueue[2];

      // Remove piece position from queue
      m_piecePosQueue.erase(m_piecePosQueue.begin(),
                            m_piecePosQueue.begin() + 3);

      // Remove piece from queue window
      m_controlWindow->removeFirstItem();

      wxLogMessage("Moving to: x=%d y:%d z:%d", x, y, z);

      // Load modbus with coordinates
      setXval(getXY(x, y).first);
      setYval(getXY(x, y).second);
      setZval(z);
      sleep_for(100ms);
      setCO();             // Tells the UR5 to load the coordinates and move
      while (getDO() != 2) // Wait for UR5 to move
      {
        sleep_for(100ms);
        if (getDO() == -1) {
          wxLogMessage("Modbus: Error getting Digital Output");
          break;
        }
      }
      // // Make chrono high_resolution_clock::now() - start_time
      // std::chrono::high_resolution_clock::time_point start_time =
      //     std::chrono::high_resolution_clock::now();
      if (grip) {
        uint8_t gripcmd[1] = {1};
        m_serial.writeBytes(gripcmd, 1);
        grip = false;
      } else {
        uint8_t gripcmd[1] = {0};
        m_serial.writeBytes(gripcmd, 1);
        grip = true;
      }
      uint8_t buffer[1];
      m_serial.readBytes(buffer, 1, 0, 100000);
      // std::chrono::high_resolution_clock::time_point end_time =
      //     std::chrono::high_resolution_clock::now();
      // std::chrono::duration<double> time_span = end_time - start_time;
      // wxLogMessage("Gripping took: %f seconds", time_span.count());
      setCO(); // Tells the UR5 continue
    } else {
      modbus_write_register(m_mb, 22,
                            val); // Prevents the modbus from timing out
      val = val == 0 ? 1 : 0;
      // If the queue is empty, wait 1 seconds and check again
      sleep_for(1s);
    }
  }
  modbus_close(m_mb);
  m_serial.closeDevice();
}

bool Robot::shouldRun() {
  // Check if queue has at least 3 elements (x, y, z)
  if (m_piecePosQueue.size() < 3) {
    return false;
  } else {
    return true;
  }
}

void Robot::moveQueue(const int &cellX, const int &cellY,
                      const wxString &operation, const wxString &id) {
  // Add piece position to queue
  m_piecePosQueue.push_back(cellX);
  m_piecePosQueue.push_back(cellY);
  m_piecePosQueue.push_back(m_zHeight);

  // Add piece position to queue window

  m_controlWindow->addItem(id, operation, getXY(cellX, cellY).first,
                           getXY(cellX, cellY).second, m_zHeight);

  if (operation == "To Outside Board") {
    setDeadPiece(cellX, cellY, id);
  }
}

void Robot::getDirection(int xCornerBR, int yCornerBR, int xCornerBL,
                         int yCornerBL) {
  // Set the values of the corners matching cell(0,0)
  m_xCorner = xCornerBR;
  m_yCorner = yCornerBR;

  // Calculate the difference between the corners
  m_dX = (xCornerBR - xCornerBL) / 7;
  m_dY = (yCornerBR - yCornerBL) / 7;
}
void Robot::setDeadPiece(const int &cellX, const int &cellY,
                         const wxString &id) {
  if (id.find("B_") != -1)
    m_controlWindow->addBlack(id, getXY(cellX, cellY).first,
                              getXY(cellX, cellY).second);
  else if (id.find("W_") != -1)
    m_controlWindow->addWhite(id, getXY(cellX, cellY).first,
                              getXY(cellX, cellY).second);
  else
    wxLogMessage("Error: Piece ID not recognized");
}

std::pair<int, int> Robot::getXY(const int &cellX, const int &cellY) {
  int xVal = m_xCorner - (cellX * m_dX) - (cellY * m_dY);
  int yVal = m_yCorner + (cellY * m_dX) - (cellX * m_dY);
  return std::make_pair(xVal, yVal);
}

void Robot::makeDialog() {
  m_dialog = new wxDialog(m_controlWindow, wxID_ANY, "Settings");
  wxCheckBox *aiCheckBox = new wxCheckBox(m_dialog, wxID_ANY, "AI");
  aiCheckBox->SetValue(false);
  aiCheckBox->Bind(wxEVT_CHECKBOX, [this](wxCommandEvent &event) {
    m_board->setEnemyIsAI(event.IsChecked());
  });
  m_xCornerBR = 0;
  m_yCornerBR = -500;
  m_xCornerBL = 203;
  m_yCornerBL = -343;
  getDirection(m_xCornerBR, m_yCornerBR, m_xCornerBL, m_yCornerBL);
  wxTextCtrl *cornerBR_X =
      new wxTextCtrl(m_dialog, wxID_ANY, std::to_string(m_xCornerBR));
  cornerBR_X->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
  cornerBR_X->Bind(wxEVT_TEXT, [this](wxCommandEvent &event) {
    m_xCornerBR = wxAtoi(event.GetString());
    getDirection(m_xCornerBR, m_yCornerBR, m_xCornerBL, m_yCornerBL);
  });

  wxTextCtrl *cornerBR_Y =
      new wxTextCtrl(m_dialog, wxID_ANY, std::to_string(m_yCornerBR));
  cornerBR_Y->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
  cornerBR_Y->Bind(wxEVT_TEXT, [this](wxCommandEvent &event) {
    m_yCornerBR = wxAtoi(event.GetString());
    getDirection(m_xCornerBR, m_yCornerBR, m_xCornerBL, m_yCornerBL);
  });

  wxTextCtrl *cornerBL_X =
      new wxTextCtrl(m_dialog, wxID_ANY, std::to_string(m_xCornerBL));
  cornerBL_X->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
  cornerBL_X->Bind(wxEVT_TEXT, [this](wxCommandEvent &event) {
    m_xCornerBL = wxAtoi(event.GetString());
    getDirection(m_xCornerBR, m_yCornerBR, m_xCornerBL, m_yCornerBL);
  });

  wxTextCtrl *cornerBL_Y =
      new wxTextCtrl(m_dialog, wxID_ANY, std::to_string(m_yCornerBL));
  cornerBL_Y->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
  cornerBL_Y->Bind(wxEVT_TEXT, [this](wxCommandEvent &event) {
    m_yCornerBL = wxAtoi(event.GetString());
    getDirection(m_xCornerBR, m_yCornerBR, m_xCornerBL, m_yCornerBL);
  });

  wxButton *okButton = new wxButton(m_dialog, wxID_OK, "OK");

  wxTextCtrl *zHeight =
      new wxTextCtrl(m_dialog, wxID_ANY, std::to_string(m_zHeight));
  zHeight->SetValidator(wxTextValidator(wxFILTER_NUMERIC));
  zHeight->Bind(wxEVT_TEXT, [this](wxCommandEvent &event) {
    m_zHeight = wxAtoi(event.GetString());
  });

  wxBoxSizer *coordsizer1 = new wxBoxSizer(wxHORIZONTAL);
  coordsizer1->AddSpacer(10);
  coordsizer1->Add(
      new wxStaticText(m_dialog, wxID_ANY, "Black bottom right: ("), 0,
      wxALIGN_CENTER_VERTICAL);
  coordsizer1->Add(cornerBR_X, 1, wxALIGN_CENTER_VERTICAL);
  coordsizer1->Add(new wxStaticText(m_dialog, wxID_ANY, ","), 0,
                   wxALIGN_CENTER_VERTICAL);
  coordsizer1->Add(cornerBR_Y, 1, wxALIGN_CENTER_VERTICAL);
  coordsizer1->Add(new wxStaticText(m_dialog, wxID_ANY, ")"), 0,
                   wxALIGN_CENTER_VERTICAL);
  coordsizer1->AddSpacer(10);

  wxBoxSizer *coordsizer2 = new wxBoxSizer(wxHORIZONTAL);
  coordsizer2->AddSpacer(10);
  coordsizer2->Add(new wxStaticText(m_dialog, wxID_ANY, "Black bottom left: ("),
                   0, wxALIGN_CENTER_VERTICAL);
  coordsizer2->Add(cornerBL_X, 0, wxALIGN_CENTER_VERTICAL);
  coordsizer2->Add(new wxStaticText(m_dialog, wxID_ANY, ","), 0,
                   wxALIGN_CENTER_VERTICAL);
  coordsizer2->Add(cornerBL_Y, 0, wxALIGN_CENTER_VERTICAL);
  coordsizer2->Add(new wxStaticText(m_dialog, wxID_ANY, ")"), 0,
                   wxALIGN_CENTER_VERTICAL);
  coordsizer2->AddSpacer(10);

  wxBoxSizer *coordsizer3 = new wxBoxSizer(wxHORIZONTAL);
  coordsizer3->AddSpacer(10);
  coordsizer3->Add(new wxStaticText(m_dialog, wxID_ANY, "Height of board: "), 0,
                   wxALIGN_CENTER_VERTICAL);
  coordsizer3->Add(zHeight, 0, wxALIGN_CENTER_VERTICAL);
  coordsizer3->AddSpacer(10);

  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(coordsizer1, 1, wxTOP, 10);
  mainSizer->Add(coordsizer2, 1, wxTOP, 10);
  mainSizer->Add(coordsizer3, 1, wxTOP, 10);
  mainSizer->Add(aiCheckBox, 1, wxLEFT | wxRIGHT | wxTOP, 10);
  mainSizer->AddSpacer(10);
  mainSizer->Add(okButton, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
  m_dialog->SetSizerAndFit(mainSizer);

  m_dialog->Show(true);
}