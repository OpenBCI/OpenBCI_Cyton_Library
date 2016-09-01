[![Stories in Ready](https://badge.waffle.io/OpenBCI/OpenBCI_32bit_Library.png?label=ready&title=Ready)](https://waffle.io/OpenBCI/OpenBCI_32bit_Library)
# OpenBCI 32bit Library

The (soon to be) official library for the OpenBCI 32bit Board. 


## Table of Contents:

1. [Minimums](#minimums)
2. [Installing](#installing)
3. [Upgrading](#upgrading)
4. [Downgrading](#downgrading)
3. [General Overview](#generalOverview)
  1. [Includes](#includes)
  2. [setup()](#setup)
  3. [loop()](#loop)
4. [System Overview](#systemOverview)
5. [Reference Guide](#referenceGuide)
  1. [Functions](#functions)
  2. [Constants](#constants)

## <a name="minimums"></a> Minimums:

You just opened your OpenBCI (congrats!) and want to get started programming the firmware right now?! Ok, ok do the following minimums!
1. Install the dongle drivers [from FTDI](http://www.ftdichip.com/FTDrivers.htm) for your operating system.
2. Download the latest Arduino IDE software from the [Arduino site](www.arduino.cc)
3. Follow the 2nd installation method "Manual install by copying ZIP file" to install the latest chipKIT-core hardware files from the [chipKIT-core wiki](http://chipkit.net/wiki/index.php?title=ChipKIT_core)

## <a name="installing"></a> Installing:

1. Download this repository zip or clone this repo (we clone directly into the `libraries` folder for development)
2. Download [OpenBCI_32bit_SD](https://github.com/OpenBCI/OpenBCI_32bit_SD)
3. Move both of the folders into your `libraries` folder (please make a folder in Arduino named libraries if you don't have one)
  * Mac OSX: User/Documents/Arduino/libraries
  * Windows: /My Documents/Arduino/libraries
4. Restart Arduino IDE
5. Open `DefaultBoard.ino` for a full featured example.
6. Hack and make awesome stuff!

## <a name="upgrading"></a> Upgrading:

Checkout the [upgrade guide](./UPGRADE_GUIDE)!

## <a name="downgrading"></a> Downgrading:

Have a bunch of custom firmware based on the original firmware? Have no fear for previous releases are [here](https://github.com/OpenBCI/OpenBCI_32bit_Library/releases) and [here for the radios if needed](https://github.com/OpenBCI/OpenBCI_Radios/releases).

## <a name="generalOverview"></a> General Overview:

Your needs dictate what you need to include! This saves a ton of precious memory space!

### <a name="includes"></a> Includes:

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

### <a name="setup"></a> setup():

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

### <a name="loop"></a> loop():

We will start with the basics here, and work our way up... The loop function can be thought of as the meat and core executor of the OpenBCI_32bit_Library functionality. Keep in mind the main purpose of this library is to stream data from the ADS1299 to the computer, that's our focus, everything takes a back seat to that.

A bare board, not using the SD, accel, or aux data must have the following:
```Arduino
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
  if (board.isSerialAvailableForRead()) {
    // Read one char and process it
    board.processChar(board.readOneSerialChar());
  }
}
```
The first `if` statement is only `true` if a `b` command is ran through the `processChar` function. The next `if` statement exploits a `volatile` interrupt driven `boolean` called `channelDataAvailable`. This interrupt driven system is new as of firmware version 2.0.0 a discussion of it can be [found here](https://github.com/OpenBCI/OpenBCI_32bit_Library/issues/22). If the ADS1299 has signaled to the Board new data is ready, the function `updateChannelData()` is executed. This function will grab new data from the Board's ADS1299 (and from the daisy's ADS1299) and store that data to the arrays: `lastBoardDataRaw`, `boardChannelDataRaw`, `meanBoardDataRaw`, `lastDaisyDataRaw`, `daisyChannelDataRaw`, `meanDaisyDataRaw`, which can be accessed to drive filters or whatever your heart desires.

## <a name="systemOverview"></a> System Overview:

If you send a packet from the Pic32 to the Device RFduino and you start it with 0x41, write 31 bytes, and follow with 0xFx (where x can be 0-F hex) then the packet will immediately be sent from the Device radio. This is counter to how if you want to send a message longer than 31 bytes (takes over two packets to transmit from Device radio to Host radio (Board to Dongle)) then you simply write the message, and that message will be sent in a multipacket format that allows it to be reassembled on the Dongle. This reassembling of data is critical to over the air programming.

# <a name="referenceGuide"></a> Reference Guide:

## <a name="functions"></a> Functions:

### accelHasNewData()

Reads a status register to see if there is new accelerometer data.

**_Returns_** {boolean}

`true` if the accelerometer has new data.

### accelUpdateAxisData()

Reads from the accelerometer to get new X, Y, and Z data. Updates the global array `axisData`.

### begin()

The function the OpenBCI board will call in `setup()`.

### beginDebug()

The function the OpenBCI board will call in setup. Turns sniff mode on and allows you to tap into the serial port that is broken out on the OpenBCI 32bit board.

You must alter `Board_Defs.h` file located:

On Mac:    
`/Users/username/Documents/Arduino/hardware/chipkit-core/pic32/variants/openbci/Board_Defs.h`
On Windows:

`C:\Users\username\Documents\Arduino\hardware\chipkit-core\pic32\variants\openbci\Board_Defs.h`

Specifically lines `311` and `313`, change `7` and `10` to `11` and `12` for `_SER1_TX_PIN` and `_SER1_RX_PIN` respectively. Check out this sweet gif if you are a visual person http://g.recordit.co/3jH01sMD6Y.gif

You will need to reflash your board! But now you can connect to pins `11` (`TX`) and `12` (`RX`) via any 3V3 serial to USB driver. Remember to use 3V3, 115200 baud, and have a common ground!

### isSerialAvailableForRead()

Called in every `loop()` and checks both `Serial0` and `Serial1` if `sniffMode` is `true`.

**_Returns_** {boolean}

`true` if there is data ready to be read.

### processChar(character)

Process one char at a time from serial port. This is the main command processor for the OpenBCI system. Considered mission critical for normal operation.

**_character_** {char}

The character to process.

**_Returns_** {boolean}

`true` if the command was recognized, `false` if not.

### readOneSerialChar()

If `isSerialAvailableForRead()` is `true` then this function is called. Reads from `Serial0` first and foremost, which comes from the RFduino. If `sniffMode` is true and `Serial0` didn't have any data, we will try to read from `Serial1`. If both are not available then we will return a `0x00` which is NOT a command that the system will recognize, aka this function has many safe guards.

**_Returns_** {char}

The character from the serial port.

### sendChannelData()

Writes channel data, aux data, and footer to serial port. This is the old way to send channel data. Based on global variables `useAux` and `useAccel` Must keep for portability. Will look to deprecate in 3.0.0.

If `useAccel` is `true` then sends data from `axisData` array and sets the contents of `axisData` to `0`.

If `useAux` is `true` then sends data from `auxData` array and sets the contents of `auxData` to `0`.

Adds stop byte `OPENBCI_EOP_STND_ACCEL`. See Constants below for more info.

### sendChannelDataWithAccel()

Writes channel data and `axisData` array to serial port in the correct stream packet format.

Adds stop byte `OPENBCI_EOP_STND_ACCEL`. See Constants below for more info.

### sendChannelDataWithRawAux()

Writes channel data and `auxData` array to serial port in the correct stream packet format.

Adds stop byte `OPENBCI_EOP_STND_RAW_AUX`. See Constants below for more info.

### sendChannelDataWithTimeAndAccel()

Writes channel data, `axisData` array, and 4 byte unsigned time stamp in ms to serial port in the correct stream packet format.

`axisData` will be split up and sent on the samples with `sampleCounter` of 7, 8, and 9 for X, Y, and Z respectively. Driver writers parse accordingly.

If the global variable `sendTimeSyncUpPacket` is `true` (set by `processChar` getting a time sync set `<` command) then:
    Adds stop byte `OPENBCI_EOP_ACCEL_TIME_SET` and sets `sendTimeSyncUpPacket` to `false`.

Else if `sendTimeSyncUpPacket` is `false` then:
    Adds stop byte `OPENBCI_EOP_ACCEL_TIME_SYNCED`

### sendChannelDataWithTimeAndRawAux()

Writes channel data, `auxData[0]` 2 bytes, and 4 byte unsigned time stamp in ms to serial port in the correct stream packet format.

If the global variable `sendTimeSyncUpPacket` is `true` (set by `processChar` getting a time sync set `<` command) then:
    Adds stop byte `OPENBCI_EOP_RAW_AUX_TIME_SET` and sets `sendTimeSyncUpPacket` to `false`.
Else if `sendTimeSyncUpPacket` is `false` then:
    Adds stop byte `OPENBCI_EOP_RAW_AUX_TIME_SYNCED`

### updateChannelData()

Called when the board ADS1299 has new data available. If there is a daisy module attached, that data is also fetched here.

### waitForNewChannelData()

Check status register to see if data is available from the ADS1299.

**_Returns_** {boolean}

`true` if data is available.  

## <a name="constants"></a> Constants:

### OPENBCI_EOP_STND_ACCEL

`0xC0` - End of standard stream packet.

### OPENBCI_EOP_STND_RAW_AUX

`0xC1` - End of stream packet with raw packet.

### OPENBCI_EOP_USER_DEFINED

`0xC2` - End of stream packet, user defined.

### OPENBCI_EOP_ACCEL_TIME_SET

`0xC3` - End of time sync up with accelerometer stream packet.

### OPENBCI_EOP_ACCEL_TIME_SYNCED

`0xC4` - End of time synced stream packet.

### OPENBCI_EOP_RAW_AUX_TIME_SET

`0xC5` - End of time sync up stream packet.

### OPENBCI_EOP_RAW_AUX_TIME_SYNCED

`0xC6` - End of time synced stream packet.
