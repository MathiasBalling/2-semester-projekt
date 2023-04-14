// Header Files
#include "Robot.h"

Robot::Robot() {
  getDirection(-103, -405, 162, -295);

  // Add the ip address of the modbus device
  m_mb = modbus_new_tcp("192.168.100.11", 502);

  // Connect to the modbus device
  if (modbus_connect(m_mb) == -1) {
    wxLogMessage("Modbus: Connection Failed!");
  } else {
    wxLogMessage("Modbus: Connection Successful!");
    m_connected = true;

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
  // modbus_connect(m_mb);
  // Write the x position to the modbus device
  int msg = modbus_write_register(m_mb, 128, val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set x!");
  }
  // modbus_close(m_mb);
}

void Robot::setYval(int val) {
  if (val < 0) {
    val = val * -1 + 2000;
  }
  // modbus_connect(m_mb);
  // Write the y position to the modbus device
  int msg = modbus_write_register(m_mb, 129, val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set y!");
  }
  // modbus_close(m_mb);
}

void Robot::setZval(int val) {
  if (val < 0) {
    val = val * -1 + 2000;
  }
  // modbus_connect(m_mb);
  // Write the z position to the modbus device
  int msg = modbus_write_register(m_mb, 130, val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set z!");
  }
  // modbus_close(m_mb);
}

void Robot::setCO(uint16_t val) {
  // modbus_connect(m_mb);
  // Write the configurable output to the modbus device
  int msg = modbus_write_register(m_mb, 31, val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't set Digital Output!");
  }
  // modbus_close(m_mb);
}

int Robot::getDO() {
  // modbus_connect(m_mb);
  // Read the digital output from the modbus device
  uint16_t val;
  int msg = modbus_read_registers(m_mb, 1, 1, &val);
  if (msg == -1) {
    wxLogMessage("Modbus: Counldn't get Digital Output!");
    return -1;
  } else {
    return val;
  }
  // modbus_close(m_mb);
}

bool Robot::isConnected() { return m_connected; }

void Robot::movePiece() {
  // To stop the thread for a specific amount of time
  using namespace std::chrono_literals;
  using namespace std::this_thread;

  // modbus_connect(m_mb);
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
      setCO(1);            // Tells the UR5 to load the coordinates and move
      while (getDO() != 2) // Wait for UR5 to move
      {
        sleep_for(200ms);
        if (getDO() == -1) {
          wxLogMessage("Modbus: Error getting Digital Output");
          break;
        }
      }
      sleep_for(3s); // Wait for grpper to close/open
      setCO(1);      // Tells the UR5 continue
    } else {
      wxLogMessage("Nothing to move, the queue is empty");
      // If the queue is empty, wait 5 seconds and check again
      sleep_for(5s);
    }
  }
  // modbus_close(m_mb);
}

bool Robot::shouldRun() {
  // Check if queue has at least 3 elements (x, y, z)
  if (m_piecePosQueue.size() < 3) {
    return false;
  } else {
    return true;
  }
}

void Robot::moveQueue(const int &cellX, const int &cellY, uint16_t z,
                      const wxString &operation, const wxString &id) {
  // Add piece position to queue
  m_piecePosQueue.push_back(cellX);
  m_piecePosQueue.push_back(cellY);
  m_piecePosQueue.push_back(z);

  // Add piece position to queue window

  m_controlWindow->addItem(id, operation, getXY(cellX, cellY).first,
                           getXY(cellX, cellY).second, z);

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
  m_dX = (xCornerBR - xCornerBL) / 8;
  m_dY = (yCornerBR - yCornerBL) / 8;
  wxLogMessage("xCorner: %d yCorner: %d dX: %d dY: %d", m_xCorner, m_yCorner,
               m_dX, m_dY);
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
