# v3.0.0

### New Features

* Add wifi shield support
   * Send channel gains to wifi shield at start of stream
   * takes ~4 seconds for the wifi shield to be reachable
* Add ability to turn external serial port `Serial1` on through commands.
* Add ability to use ESP8266 through SPI port.
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

### Enhancements

* `hasDataSerial0` and `hasDataSerial1` use new properties `SerialInfo` to determine if data should be received. Now safe to call every loop.

### Breaking Changes

* Removed boolean `useAccel` in support of new mode paradigm. To use the accel, do nothing, it's enabled by default, to not use the accel simply call `useAccel(false)` and this library will automatically send the contents of `auxData` array each packet.
* Removed `OPENBCI_EOP_STND_ACCEL`, `OPENBCI_EOP_STND_RAW_AUX`, `OPENBCI_EOP_USER_DEFINED`, `OPENBCI_EOP_ACCEL_TIME_SET`, `OPENBCI_EOP_ACCEL_TIME_SYNCED`, `OPENBCI_EOP_RAW_AUX_TIME_SET`, and `OPENBCI_EOP_RAW_AUX_TIME_SYNCED` in place of `enum` support replacement: `PACKET_TYPE_ACCEL`, `PACKET_TYPE_RAW_AUX`, `PACKET_TYPE_USER_DEFINED`, `PACKET_TYPE_ACCEL_TIME_SET`, `PACKET_TYPE_ACCEL_TIME_SYNC`, `PACKET_TYPE_RAW_AUX_TIME_SET`, and `PACKET_TYPE_RAW_AUX_TIME_SYNC`.
* Removed `sniffMode` in place for `curBoardMode == OPENBCI_BOARD_MODE_DEBUG`
* Removed public `waitForNewChannelData()`
* Removed public `timeSynced` and private `sendTimeSyncUpPacket`

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
