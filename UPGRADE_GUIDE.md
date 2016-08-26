# OpenBCI 32bit Upgrade Guide

The purpose of this document is to provide instruction, resources, and advice for upgrading an OpenBCI 32bit 8-16 channel board firmware.

## Upgrading to 2.0.0

You must re-program three (3) different microcontrollers: Chipkit Pic32 (hereafter called `Pic`) on the `Board`, RFduino on the `Board` (hereafter called `Device`), and the RFdunio on the `Dongle` (hereafter called `Host`).

The order of programming should go as follows

1. Flash the `Device`
2. Flash the `Host`
3. Flash the `Pic`
