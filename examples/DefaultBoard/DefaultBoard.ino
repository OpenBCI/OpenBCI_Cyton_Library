#include <DSPI.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>

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

    // Verify the SD file is open
    if(SDfileOpen) {
        // Write to the SD card
        writeDataToSDcard(board.sampleCounter);
    }

    // Send standard packet with channel data
    board.sendChannelData();
  }

  // Check the serial port for new data
  if (board.isSerialAvailableForRead()) {
    // Read one char from the serial port
    char newChar = board.readOneSerialChar();

    // Send to the sd library for processing
    sdProcessChar(newChar);

    // Send to the board library
    board.processChar(newChar);
  }
}
