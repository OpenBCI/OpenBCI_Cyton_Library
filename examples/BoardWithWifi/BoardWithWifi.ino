#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

// THIS IS NOT COMPLETE OR WORKING!

void setup() {
  // Bring up the OpenBCI Board
  board.begin();
  board.beginSecondarySerial();

}

void loop() {

    if (board.streaming) {
        if (board.channelDataAvailable) {
            // Read from the ADS(s), store data, set channelDataAvailable flag to false
            board.updateChannelData();

            if (board.timeSynced) {
                board.sendChannelDataWithTimeAndRawAux();
            } else {
                // Send standard packet with channel data
                board.sendChannelDataWithRawAux();
            }
        }
    }

    // Check the serial port for new data
    if (Serial0.available()) {
        char newChar = board.getCharSerial0();
        // Read one char and process it
        board.processChar(newChar);

        if (newChar == 'h') {
            Serial1.print("AT");
        } else if (newChar == 'k') {
            Serial1.print("AT+RST");
        } else if (newChar == 'n') {
            Serial1.print("AT+GMR");
        } else if (newChar == 'N') {
            Serial1.print("AT+CWMODE=3");
        } else if (newChar == 'o') {
            Serial1.print("AT+CWJAP="",""");
        } else if (newChar == 'O') {
            Serial1.print("AT+CWJAP?");
        } else if (newChar == 'V') {
            Serial1.print("AT+CWLAP");
        }
    }

    if (board.hasDataSerial1()) {
        Serial0.write(Serial1.read());
    }
}
