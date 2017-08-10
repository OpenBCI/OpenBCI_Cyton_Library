# OpenBCI 32bit Upgrade Guide

The purpose of this document is to provide instruction, resources, and advice for upgrading an OpenBCI Cyton 8-16 channel board firmware.

## Upgrading to 3.0.0

### Upgrading from 2.x.x

Flash the `Pic` with [`DefaultBoard`](https://github.com/OpenBCI/OpenBCI_32bit_Library/blob/master/examples/DefaultBoard/DefaultBoard.ino)

#### Awesome New Features

* Wifi shield support
* Read from analog or digital ports in a single line or command. (board mode)
* Simplified user experience
* Variable sample rate with wifi shield or Serial1 (with baud of 468000)

#### What this update set out to solve

* Have a single `.sendChannelData()` data function to call that manages the stop byte behind the scenes. I.e. if accel data should be added to aux bytes vs. reading from analog input pins and putting that in the aux bytes.
* Add wifi support without breaking any firmware v2.0.0 or v1.0.0 features.
* Prevent users from having to upload custom code to the pic

#### In depth tutorials
* [How to get/install/upload code to Pic32 `Board`](http://docs.openbci.com/tutorials/02-Upload_Code_to_OpenBCI_Board#upload-code-to-openbci-board-32bit-upload-how-to-firmware-version-2xx-fall-2016)

#### New commands

* [Set Board Mode]()
* [Set sample rate]()
* [Wifi attach/remove/status]()

### Upgrading from 1.x.x

Read *Upgrading to 2.0.0* below:

## Upgrading to 2.0.0

You must re-program three (3) different microcontrollers: Chipkit Pic32 (hereafter called `Pic`) on the `Board`, RFduino on the `Board` (hereafter called `Device`), and the RFdunio on the `Dongle` (hereafter called `Host`).

The order of programming should go as follows

1. Flash the `Device` with [`RadioDevice32bit`](https://github.com/OpenBCI/OpenBCI_Radios/blob/master/examples/RadioDevice32bit/RadioDevice32bit.ino)
2. Flash the `Host` with [`RadioHost32bit`](https://github.com/OpenBCI/OpenBCI_Radios/blob/master/examples/RadioHost32bit/RadioHost32bit.ino)
3. Flash the `Pic` with [`DefaultBoard`](https://github.com/OpenBCI/OpenBCI_32bit_Library/blob/master/examples/DefaultBoard/DefaultBoard.ino)

## Awesome New Features

* Examples folder contains a bunch of awesome code to get you started as fast as possible!
* Time syncing
* Send custom packet types for your openbci driver to decipher!
* Send user defined packet types (let's you do custom code on the pic and still use our high speed mode!)
* Change baud rate on `Host` to `230400` or `921600`
* Change radio channel number from the computer

## What this update set out to solve

* Removed burger code. Now you can send strings of commands from a driver instead of one at a time.
* Moved mission critical code into library. Play around in the `.ino` files without breaking the core features of the board.
* Over the air (OTA) programming stabilization.
* Always send `$$$` after any text send from the board. (i.e. `d` and `c` just sent text with not `$$$`)

## Resources
### In depth tutorials
* [How to get/install/upload code to Pic32 `Board`](http://docs.openbci.com/Hardware/05-Cyton_Board_Programming_Tutorial)
* [How to get/install/upload code to `Host` and `Device`](http://docs.openbci.com/Hardware/06-Cyton_Radios_Programming_Tutorial)
* [Packet protocol, including the new stop byte](http://docs.openbci.com/Hardware/03-Cyton_Data_Format)

### New commands
* [Time stamping/syncing commands](http://docs.openbci.com/OpenBCI%20Software/04-OpenBCI_Cyton_SDK#firmware-v200-new-commands-time-stamping)
* [Radio channel commands](http://docs.openbci.com/OpenBCI%20Software/04-OpenBCI_Cyton_SDK#firmware-v200-new-commands-radio-configuration-commands)

## Installing Previous Versions

To install previous versions of the firmware checkout the `Releases` folder to download 1.0.0:
* [OpenBCI_32bit_Library 1.0.0](https://github.com/OpenBCI/OpenBCI_32bit_Library/releases/tag/v1.0.0)
* [OpenBCI_Radios](https://github.com/OpenBCI/OpenBCI_Radios/releases/tag/v1.0)
