#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

void setup() {
  // Bring up the OpenBCI Board
  board.begin();
}

void loop() {

  if (board.streaming) {
    // Wait for the ADS to signal it's ready with new data
    while (!board.isADSDataAvailable()) {}

    // Read from the ADS(s) and store data into
    board.updateChannelData();

    // Send standard packet with channel data
    board.sendChannelData();
  }

  // Check the serial port for new data
  if (board.isSerialAvailableForRead()) {
    // Read one char and process it
    board.processChar(board.readOneSerialChar());
  }
}
