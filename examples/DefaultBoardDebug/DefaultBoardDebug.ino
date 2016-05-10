#include <OBCI32_SD.h>
#include <DSPI.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>

// Booleans Required for SD_Card_Stuff.ino
boolean addAccelToSD = false; // On writeDataToSDcard() call adds Accel data to SD card write
boolean addAuxToSD = false; // On writeDataToSDCard() call adds Aux data to SD card write
boolean SDfileOpen = false; // Set true by SD_Card_Stuff.ino on successful file open

void setup() {
  // Bring up the OpenBCI Board
  board.beginDebug(); // Allows us to sniff the port

  // Notify the board we want to use accel data
  board.useAccel = true;
}

void loop() {
  if (board.streaming) {
    // Wait for the ADS to signal it's ready with new data
    while (board.waitForNewChannelData()) {
        // Could do tiny maintiance tasks here
    }

    // Read from the ADS(s) and store data into
    board.updateChannelData();

    // Check to see if accel has new data
    if(board.accelHasNewData()){
        // Get new accel data
        board.accelUpdateAxisData();

        // Tell the SD_Card_Stuff.ino to add accel data in the next write to SD
        addAccelToSD = true; // Set false after writeDataToSDcard()
    }

    // Verify the SD file is open
    if(SDfileOpen) {
        // Write to the SD card, writes aux data
        writeDataToSDcard(board.sampleCounter);
    }


    if (board.timeSynced) {
        // Send time synced packet with channel data, current board time, and an accel reading
        //  X axis is sent on sampleCounter % 10 == 0
        //  Y axis is sent on sampleCounter % 10 == 1
        //  Z axis is sent on sampleCounter % 10 == 2
        board.sendChannelDataWithTimeAndAccel();
    } else {
        // Send standard packet with channel data
        board.sendChannelDataWithAccel();
    }

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
