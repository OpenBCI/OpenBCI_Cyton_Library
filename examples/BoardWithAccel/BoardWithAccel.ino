#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  // Notify the board we want to use accel data
  board.useAccel = true;
}

void loop() {

  // The main dependency of this single threaded microcontroller is to
  //  stream data from the ADS.
  if (board.streaming) {
    // Wait for the ADS to signal it's ready with new data
    while (board.waitForNewChannelData()) {}

    // Read from the ADS(s) and store data into
    board.updateChannelData();

    // Check to see if accel has new data
    if(board.accelHasNewData()){
        // Get new accel data
        board.accelUpdateAxisData();

        // Tell the SD_Card_Stuff.ino to add accel data in the next write to SD
        addAccelToSD = true;
    }

    // Send standard packet with channel data and accel data
    board.sendChannelData();
  }

  // Check the serial port for new data
  if (board.isSerialAvailableForRead()) {
    // Read one char and process it
    board.processChar(board.readOneSerialChar());
  }
}
