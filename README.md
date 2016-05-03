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

### Includes Needed

Your needs dictate what libraries you need to include!

To use the SD card:
```Arduino
#include <OBCI32_SD.h>
#include <DSPI.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>
```

To use the board without the SD card:
```Arduino
#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>
```

### Definitions Needed for SD card


### Setup() Function
