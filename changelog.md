# v3.0.0

### New Features

* Add wifi shield support.
   * Simply add [OpenBCI_Wifi_Master](https://github.com/OpenBCI/OpenBCI_Wifi_Master_Library) to your `DefaultBoard.ino` and add `wifi.loop()` to your loop function. If you want to read from it checkout the `DefaultBoard.ino` for it's simple interface.
   * Send channel gains to wifi shield at start of stream
   * takes ~4 seconds for the wifi shield to be reachable
* Add ability to turn external serial port `Serial1` on through commands.
* Change board types on the fly! No longer do you have to upload new code to the Cyton's Pic32 just to do an analog read. You can now read from analog or digital pins with the press send of a code! `/` now sets the board mode, where:
   * BOARD_MODE_DEFAULT is `0`
   * BOARD_MODE_DEBUG is `1`
   * BOARD_MODE_ANALOG is `2`
   * BOARD_MODE_DIGITAL is `3`
* Add loop function for internal timing operations related to power on reset for wifi shield, remove `loop` to free up pins and such and remove wifi capability.
* Add function to turn time stamps on `useTimeStamp(true)`, time stamps are disabled by default. Note the Wifi shield will use NTP time stamps.
* Add wifi commands:
   * _OpenBCI Wifi Attach_ - `{`
   * _OpenBCI Wifi Remove_ - `}`
   * _OpenBCI Wifi Status_ - `:`
   * _OpenBCI Wifi Reset_ - `;`
* Variable sample rate in the format of **~(COMMAND)**. This works similar to the Channel Settings commands, however, there is no latching character. Changing the sample rate requires sending a `v` or soft-reset to ensure all systems are correct. Power cycling the OpenBCI board will cause the sample rate to reset back to default of 250Hz. **IMPORTANT!** The Cyton cannot and will not stream data over 250SPS. Plug in the wifi shield to get speeds over 250SPS streaming. You may still write to an SD card though, the firmware will not send EEG data over the Bluetooth radios. Check out the new commands:
   * 0 = 16000 Hz
   * 1 = 8000 Hz
   * 2 = 4000 Hz
   * 3 = 2000 Hz
   * 4 = 1000 Hz
   * 5 = 500 Hz
   * 6 = 250 Hz
   * ~ = Get current sample rate
   * **EXAMPLE**
      * First, user sends **~~**
      * **returns** `Sample rate is 250Hz$$$`
      * Then, user sends **~5**
      * **returns** Sample rate set to 500Hz$$$

### Enhancements

* `hasDataSerial0` and `hasDataSerial1` use new properties `SerialInfo` to determine if data should be received. Now safe to call every loop.

### Breaking Changes

* Removed boolean `useAccel` in support of new mode paradigm. To use the accel, do nothing, it's enabled by default, to not use the accel simply call `useAccel(false)` and this library will automatically send the contents of `auxData` array each packet.
* Removed `OPENBCI_EOP_STND_ACCEL`, `OPENBCI_EOP_STND_RAW_AUX`, `OPENBCI_EOP_USER_DEFINED`, `OPENBCI_EOP_ACCEL_TIME_SET`, `OPENBCI_EOP_ACCEL_TIME_SYNCED`, `OPENBCI_EOP_RAW_AUX_TIME_SET`, and `OPENBCI_EOP_RAW_AUX_TIME_SYNCED` in place of `enum` support replacement: `PACKET_TYPE_ACCEL`, `PACKET_TYPE_RAW_AUX`, `PACKET_TYPE_USER_DEFINED`, `PACKET_TYPE_ACCEL_TIME_SET`, `PACKET_TYPE_ACCEL_TIME_SYNC`, `PACKET_TYPE_RAW_AUX_TIME_SET`, and `PACKET_TYPE_RAW_AUX_TIME_SYNC`.
* Removed `sniffMode` in place for `curBoardMode == OPENBCI_BOARD_MODE_DEBUG`
* Removed public `waitForNewChannelData()`
* Removed public `timeSynced` and private `sendTimeSyncUpPacket`
* Setting internal test signal now, when not streaming, returns a success message, with EOT `$$$`

## Beta3

The overall goal was to clean the wifi code out of the library so it would not be needed when you are building a bare board. 

### Bug Fixes

* Fixed the `BoardWithAnalogSensor.ino`, `BoardWithDigitalRead.ino` and `BoardWithCustomData.ino` examples.

### Breaking Changes

* Removed all wifi code and put into [new library](https://github.com/OpenBCI/OpenBCI_Wifi_Master_Library) that must be included! The new library is a called [OpenBCI_Wifi_Master_Library](https://github.com/OpenBCI/OpenBCI_Wifi_Master_Library). It is simply included when wifi is wanted.
* Removed `.loop()` function from library.

### Files

* Add `BoardWithWifi.ino` example that shows a bare board with just wifi. No SD or ACCEL for example.

## Beta2

### Breaking Changes

* Setting internal test signal now, when not streaming, returns a success message, with EOT $$$

## Beta1

* Initial Release

# v2.0.1

### Bug Fixes
* Bug where softReset message could be scrambled on daisy board.

### Breaking Changes
* Renamed `BasicBoard.ino` to `BoardNoAccelOrSD.ino` to avoid confusion. Thanks @wjcroft for the suggestion.
* Renamed `BasicBoardDebug.ino` to `BoardNoAccelOrSDDebug.ino` to avoid confusion. Thanks @wjcroft for the suggestion.

# v2.0.0-rc.6

### New Features

* Add `hasDataSerial0`, `hasDataSerial1`, `getCharSerial0`, and `getCharSerial1`
* Add `channelDataAvailable` boolean variable to check each loop to see if new data is available.

### Breaking Changes

* Removed `isSerialAvailableForRead`

### Work In Progress

* Add ability to change board mode on the fly.

# 2.0.0

### Bug Fixes

* Sending `d` did not terminate with an EOT (`$$$`)
* Sending `c` did not terminate with an EOT (`$$$`)
