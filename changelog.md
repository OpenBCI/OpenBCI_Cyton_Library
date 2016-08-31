# v3.0.0

### Breaking Changes

* Removed boolean `useAccel` in support of new mode paradigm. To use the accel simply set `curAccelMode` to `ACCEL_MODE_ON` or a function call `useAccel()`. You can also turn off the excel with a call to `useAccel(false)`.
* Removed `OPENBCI_EOP_STND_ACCEL`, `OPENBCI_EOP_STND_RAW_AUX`, `OPENBCI_EOP_USER_DEFINED`, `OPENBCI_EOP_ACCEL_TIME_SET`, `OPENBCI_EOP_ACCEL_TIME_SYNCED`, `OPENBCI_EOP_RAW_AUX_TIME_SET`, and `OPENBCI_EOP_RAW_AUX_TIME_SYNCED` in place of `enum` support replacement: `PACKET_TYPE_ACCEL`, `PACKET_TYPE_RAW_AUX`, `PACKET_TYPE_USER_DEFINED`, `PACKET_TYPE_ACCEL_TIME_SET`, `PACKET_TYPE_ACCEL_TIME_SYNC`, `PACKET_TYPE_RAW_AUX_TIME_SET`, and `PACKET_TYPE_RAW_AUX_TIME_SYNC`;

# v2.0.0-rc.7

### New Features

* Change board types on the fly!

### Breaking Changes

* Removed `sniffMode` in place for `curBoardMode == OPENBCI_BOARD_MODE_DEBUG`

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
