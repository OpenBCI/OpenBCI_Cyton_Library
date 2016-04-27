#include <DSPI.h>
#include <EEPROM.h>
#include <OpenBCI_32bit.h>
#include <OpenBCI_32bit_Definitions.h>

void setup() {
  // Bring up the OpenBCI Board
  board.beginDebug();
}

void loop() {

  if (board.streaming) {
    while (!board.isADSDataAvailable()) {} // wait for DRDY pin...

    board.updateChannelData();
    // Can now send channel data
    board.sendChannelData();
  }

  // Check to see if there is new data available
  if (board.isSerialAvailableForRead()) {
    char newChar = board.readOneSerialChar();
    boolean cmd_recognized = false;
    // Send to SD first
    sd.processChar(newChar);
    // Send to Board
    board.processChar(newChar);
  }
}
