# v2.0.1

### Bug Fixes
* Bug where softReset message could be scrambled on daisy board.

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
