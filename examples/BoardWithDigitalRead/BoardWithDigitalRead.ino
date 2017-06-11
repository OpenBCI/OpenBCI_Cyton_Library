#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  // Notify the board we want to use aux data, this effects `::sendChannelData()`
  board.useAccel(false);

  // Set pin to input A0-A5 can be digital input
  pinMode(17, INPUT);
}

void loop() {
  board.loop();
  // The main dependency of this single threaded microcontroller is to
  //  stream data from the ADS.
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();

      // Read from the digital input and store auxiliary position 0
      // take a reading from the ADC. Result range from 0 to 1023
      board.auxData[0] = digitalRead(17);

      // Send packet with channel data and auxData contents
      board.sendChannelData();
    }
  }

  // Check the serial port for new data
  if (board.hasDataSerial0()) {
    // Read one char and process it
    board.processChar(board.getCharSerial0());
  }
}
