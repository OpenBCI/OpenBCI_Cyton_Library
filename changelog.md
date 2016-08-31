# v3.0.0

### Breaking Changes

* Removed boolean `useAccel` in support of new mode paradigm. To use the accel simply set `curAccelMode` to `ACCEL_MODE_ON` or a function call `useAccel()`. You can also turn off the excel with a call to `useAccel(false)`.

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
