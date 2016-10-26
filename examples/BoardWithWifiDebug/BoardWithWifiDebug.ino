#include <DSPI.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>

int packetSendIntervalMs = 50; // 50 ms
unsigned long lastPacketSent = millis();


void setup() {

  // Notify the board we want to use accel data
  // board.wifi.rx = false;
  board.iWifi.tx = true;

  // Bring up the OpenBCI Board
  board.begin();
  // Change the sample rate
  // board.curSampleRate = board.SAMPLE_RATE_500;

  board.streaming = true;
}

void loop() {
  if (millis() > lastPacketSent + packetSendIntervalMs) {
    board.sendChannelData();
    lastPacketSent = millis();
  }


  // Check serial 0 for new data
  if (board.hasDataSerial0()) {
    // Read one char from the serial 0 port
    char newChar = board.getCharSerial0();
    //
    if (Serial0) {
       Serial0.print("Recieved char from serial0 ");
       Serial0.println(newChar);
    }

    // Send to the board library
    board.processChar(newChar);
  }
}
