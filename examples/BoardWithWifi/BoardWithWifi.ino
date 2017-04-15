#include <DSPI.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>

void setup() {

  // Notify the board we want to use accel data
  // board.useAccel(true);

  board.iWifi.rx = true;
  board.iWifi.tx = true;

  board.curSampleRate = board.SAMPLE_RATE_500;

  // Bring up the OpenBCI Board
  board.begin();

  // Change the sample rate
  board.iSerial0.tx = false;

  board.timeSynced = true;
}

void loop() {
  board.loop();
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();

      // Check to see if accel has new data
      if(board.accelHasNewData()) {
        // Get new accel data
        board.accelUpdateAxisData();
      }
      if (board.timeSynced) {
        // Send time synced packet with channel data, current board time, and an accel reading
        //  X axis is sent on sampleCounter % 10 == 7
        //  Y axis is sent on sampleCounter % 10 == 8
        //  Z axis is sent on sampleCounter % 10 == 9
        board.sendChannelData(board.PACKET_TYPE_ACCEL_TIME_SYNC);
      } else {
        // Send standard packet with channel data
        board.sendChannelData(board.PACKET_TYPE_ACCEL);
      }
      // Send time synced packet with channel data, current board time, and an accel reading
    }
  }

  // Check serial 0 for new data
  if (board.hasDataSerial0()) {
    // Read one char from the serial 0 port
    char newChar = board.getCharSerial0();
    //
    // if (Serial1) {
    //   Serial1.print("Recieved char from serial0 ");
    //   Serial1.println(newChar);
    // }

    // Send to the board library
    board.processChar(newChar);
  }

  if (board.hasDataSerial1()) {
    // Read one char from the serial 1 port
    char newChar = board.getCharSerial1();

    // if (Serial1) {
    //   Serial1.print("Recieved char from serial1 ");
    //   Serial1.println(newChar);
    // }

    // Read one char and process it
    board.processChar(newChar);
  }
}
