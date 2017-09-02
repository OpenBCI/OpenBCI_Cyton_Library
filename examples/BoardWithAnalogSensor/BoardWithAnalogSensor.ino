#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

// NOTE: THIS DOES NOT HAVE SD

void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  // Read from the analog sensor and store auxiliary position 0
  // take a reading from the ADC. Result range from 0 to 1023
  // Will put 10 bits from:
  //  Aux 1:2 D11 (A5)
  //  Aux 3:4 D12 (A6)
  //  Aux 5:6 D17 (A7)
  board.setBoardMode(board.BOARD_MODE_ANALOG);
}

void loop() {
  // The main dependency of this single threaded microcontroller is to
  //  stream data from the ADS.
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();

      // Send standard packet with channel data and aux data
      board.sendChannelData();
    }
  }

  // Check the serial ports for new data
  if (board.hasDataSerial0()) board.processChar(board.getCharSerial0());
  if (board.hasDataSerial1()) board.processChar(board.getCharSerial1());
  board.loop();
}
