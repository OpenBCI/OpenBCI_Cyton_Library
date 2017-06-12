#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  // Read from digital input and store auxiliary position 0
  // take a reading from the ADC. Result range from 0 to 1023
  // Will put 10 bits from:
  //  Aux 1:2 D11
  //  Aux 3:4 D12
  //  Aux 5:6 D17
  board.setBoardMode(BOARD_MODE_DIGITAL);
}

void loop() {
  board.loop();
  // The main dependency of this single threaded microcontroller is to
  //  stream data from the ADS.
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();

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
