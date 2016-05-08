# OpenBCI_32bit_Library

The official library for the OpenBCI 32bit Board.

## Minimums
You just opened your OpenBCI (congrats!) and want to get started programming the firmware right now?! Ok, ok do the following minimums!
1. Install the dongle drivers [from FTDI](http://www.ftdichip.com/FTDrivers.htm) for your operating system.
2. Download the latest Arduino IDE software from the [Arduino site](www.arduino.cc)
3. Follow the 2nd installation method "Manual install by copying ZIP file" to install the latest chipKIT-core hardware files from the [chipKIT-core wiki](http://chipkit.net/wiki/index.php?title=ChipKIT_core)

## Installing this library
1. Download this repository zip or clone this repo
2. Move **entire** folder into libraries folder (please make a folder in Arduino named libraries if you don't have one)
  * Mac OSX: User/Documents/Arduino/libraries
  * Windows: /My Documents/Arduino/libraries
3. Restart Arduino IDE
4. Open `DefaultBoard.ino` for a full featured example.
5. Hack and make awesome stuff!

## General Overview
Your needs dictate what you need to include! This saves a ton of precious memory space!

### Pre-setup

#### Default OpenBCI with SD Card Functionality

In order to use the SD card write functionality, you must not only include the file `SD_Card_Stuff.ino` located in examples/DefaultBoard, you must include the following:

Headers:
```Arduino
#include <OBCI32_SD.h>
#include <DSPI.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>
```

Variables used by `SD_Card_Stuff.ino`:
```Arduino
boolean addAccelToSD = false;
boolean addAuxToSD = false;
boolean SDfileOpen = false;
```

#### Bare OpenBCI Board with no SD card

Headers:
```Arduino
#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>
```

You do not need to declare any variables...

### setup()

#### Accel (default)
```Arduino
void setup() {
  board.begin(); // Bring up the OpenBCI Board
  board.useAccel = true; // Notify the board we want to use accel data, this effects `::sendChannelData()`
}
```

#### Aux
```Arduino
void setup() {
  board.begin(); // Bring up the OpenBCI Board
  board.useAux = true; // Notify the board we want to use aux data, this effects `::sendChannelData()`
}
```

#### Bare board
```Arduino
void setup() {
  board.begin(); // Bring up the OpenBCI Board
}
```

## loop()
We will start with the basics here, and work our way up... The loop function can be thought of as the meat and core executor of the OpenBCI_32bit_Library functionality. Keep in mind the main purpose of this library is to stream data from the ADS1299 to the computer, that's our focus, everything takes a back seat to that.

A bare board, not using the SD, accel, or aux data must have the following:
```Arduino
void loop() {

  if (board.streaming) {
    // Wait for the ADS to signal it's ready with new data
    while (board.waitForNewChannelData()) {}

    // Read from the ADS(s) and store data into
    board.updateChannelData();

    // Send standard packet with channel data
    board.sendChannelData();
  }

  // Check the serial port for new data
  if (board.isSerialAvailableForRead()) {
    // Read one char and process it
    board.processChar(board.readOneSerialChar());
  }
}
```

## System Overview

If you send a packet from the Pic32 to the Device RFduino and you start it with 0x41, write 31 bytes, and follow with 0xFx (where x can be 0-F hex) then the packet will immediately be sent from the Device radio. This is counter to how if you want to send a message longer than 31 bytes (takes over two packets to transmit from Device radio to Host radio (Board to Dongle)) then you simply write the message, and that message will be sent in a multipacket format that allows it to be reassembled on the Dongle. This reassembling of data is critical to over the air programming. 
