// Contributed example by Irene Vigue Guix (@viguix)

#include <DSPI.h>
#include <OBCI32_SD.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>

// Booleans Required for SD_Card_Stuff.ino
boolean addAccelToSD = false; // On writeDataToSDcard() call adds Accel data to SD card write
boolean addAuxToSD = false; // On writeDataToSDCard() call adds Aux data to SD card write
boolean SDfileOpen = false; // Set true by SD_Card_Stuff.ino on successful file open

// 2 Button External Trigger Code
// --------------------------------------------------------
//  << EXTERNAL TRIGGER FROM RIGHT AND LEFT PUSHBUTTON >>
int leftButton = 17;          // left button
int rightButton = 18;         // right button
int leftButtonValue;          // used to hold the latest button reading
int rightButtonValue;
int lastLeftButtonValue;      // used to remember the last button state
int lastRightButtonValue;
// --------------------------------------------------------

void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  // Notify the board we don't want to use accel data and use aux
  board.useAccel(false);

  // Configure two external triggers
  pinMode(leftButton, INPUT);    // set the button pin direction
  pinMode(rightButton, INPUT);
  leftButtonValue = lastLeftButtonValue = digitalRead(leftButton); // seed
  rightButtonValue = lastRightButtonValue = digitalRead(rightButton); // seed​
}

void loop() {
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();

      // Read the left button value
      leftButtonValue = digitalRead(leftButton);
      if (leftButtonValue != lastLeftButtonValue) {  // if it's changed,
        if (leftButtonValue == HIGH){    // if it's gone from LOW to HIGH
          // 0x6220 converts to PI in GUI
          board.auxData[0] = 0x6220;
          addAuxToSD = true;             // add Aux Data to the SD card if it's there
        }
        lastLeftButtonValue = leftButtonValue; // keep track of the changes
      }

      // Read the right button value
      rightButtonValue = digitalRead(rightButton);
      if (rightButtonValue != lastRightButtonValue){  // if it's changed,
        if (rightButtonValue == HIGH){    // if it's gone from LOW to HIGH
          // 0x6220 converts to PI in GUI
          board.auxData[1] = 0x6220;
          addAuxToSD = true;             // add Aux Data to the SD card if it's there
        }
        lastRightButtonValue = rightButtonValue; // keep track of the changes
      }

      // Verify the SD file is open
      if(SDfileOpen) {
        // Write to the SD card, writes aux data
        writeDataToSDcard(board.sampleCounter);
      }

      // Send standard packet with channel data and aux data
      //  includes aux data because we set told the board to add it
      board.sendChannelData();
    }
  }

  // Check the serial port for new data
  if (board.hasDataSerial0()) {
    // Read one char from the serial port
    char newChar = board.getCharSerial0();

    // Send to the sd library for processing
    sdProcessChar(newChar);

    // Send to the board library
    board.processChar(newChar);

    // Custom commands for motor imagery tagging
    switch (newChar) {
      case 'f':
         board.auxData[2] = 1;
         break;
      case 'g':
         board.auxData[2] = 2;
         break;
      case 'k':
         board.auxData[2] = 3;
         break;
      case 'l':
         board.auxData[2] = 4;
         break;
    }
  }
  board.loop();
}
