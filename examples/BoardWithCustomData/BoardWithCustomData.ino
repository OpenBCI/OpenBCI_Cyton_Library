#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

unsigned long timer = 0;
byte LEDState = 0;

void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  timer = millis();

  LEDState = 1;
  digitalWrite(OPENBCI_PIN_LED,HIGH);

}

void loop() {
  // Downsample
  if ((millis() - timer) > 10) {
    // Save new time
    timer = millis();
    sendLEDStatus();
  }

  // Check the serial port for new data
  if (board.hasDataSerial0()) {
    // Read one char and process it
    char c = board.getCharSerial0();

    if (c == '0') {
      // Make the LED turn OFF when a '0' is sent from the PC
      digitalWrite(OPENBCI_PIN_LED,LOW);
      LEDState = 0;
    } else if (c == '1') {
      // Make the LED turn ON when a '1' is sent from the PC
      digitalWrite(OPENBCI_PIN_LED,HIGH);
      LEDState = 1;
    }
  }
}

void sendLEDStatus() {
  // Must have header byte
  Serial0.write('A'); // 0x41 1 byte
  // Write the LED state
  Serial0.write(LEDState); // 1 byte
  // Fill the rest with fake data
  for (int i = 0; i < 30; i++) {
    Serial0.write((uint8_t)0x00);
  }
  // Send a stop byte with an `B` or `1011` in the last nibble to indicate a
  //  different packet type.
  Serial0.write(0xCB); // 1 byte
}
