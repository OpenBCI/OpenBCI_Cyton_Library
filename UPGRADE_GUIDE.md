# OpenBCI 32bit Upgrade Guide

The purpose of this document is to provide instruction, resources, and advice for upgrading an OpenBCI 32bit 8-16 channel board firmware.

## Upgrading to 2.0.0

You must re-program three (3) different microcontrollers: Chipkit Pic32 (hereafter called `Pic`) on the `Board`, RFduino on the `Board` (hereafter called `Device`), and the RFdunio on the `Dongle` (hereafter called `Host`).

The order of programming should go as follows

1. Flash the `Device` with [`RadioDevice32bit`](https://github.com/OpenBCI/OpenBCI_Radios/blob/2.0.0/examples/RadioDevice32bit/RadioDevice32bit.ino)
2. Flash the `Host` with [`RadioHost32bit`](https://github.com/OpenBCI/OpenBCI_Radios/blob/2.0.0/examples/RadioHost32bit/RadioHost32bit.ino)
3. Flash the `Pic` with [`DefaultBoard`](https://github.com/OpenBCI/OpenBCI_32bit_Library/blob/2.0.0/examples/DefaultBoard/DefaultBoard.ino)

### Awesome New Features

* Examples folder contains a bunch of awesome code to get you started as fast as possible!
* Time syncing
* Send custom packet types for your openbci driver to decipher!
* Send user defined packet types (let's you do custom code on the pic and still use our high speed mode!)
* Change baud rate on `Host` to `230400` or `921600`
* Change radio channel number from the computer

### What this update set out to solve

* Removed burger code. Now you can send strings of commands from a driver instead of one at a time.
* Moved mission critical code into library. Play around in the `.ino` files without breaking the core features of the board.
* Over the air (OTA) programming stabilization.
* Always send `$$$` after any text send from the board. (i.e. `d` and `c` just sent text with not `$$$`)

## Installing Previous Versions

To install previous versions of the firmware checkout the `Releases` folder to download 1.0.0:
* [OpenBCI_32bit_Library 1.0.0](https://github.com/OpenBCI/OpenBCI_32bit_Library/releases/tag/v1.0.0)
* [OpenBCI_Radios](https://github.com/OpenBCI/OpenBCI_Radios/releases/tag/v1.0)
