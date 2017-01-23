#include <DSPI.h>

int packetSendIntervalMs = 100; // 50 ms
unsigned long lastPacketSent = millis();
const int packetSize = 32;
uint8_t buf[packetSize];
uint8_t WIFI_SS = 13;

DSPI0 spi;  // use DSPI library

boolean streaming = false;
boolean wifi = false;

void setup() {


  buf[1] = (uint8_t)'A';
  buf[2] = (uint8_t)'J';
  buf[3] = (uint8_t)' ';
  buf[4] = (uint8_t)'K';
  buf[5] = (uint8_t)'E';
  buf[6] = (uint8_t)'L';
  buf[7] = (uint8_t)'L';
  buf[8] = (uint8_t)'E';
  buf[9] = (uint8_t)'R';

  pinMode(WIFI_SS,OUTPUT); digitalWrite(WIFI_SS,HIGH);

  spi.begin();
  spi.setSpeed(10000000);  // use 4MHz for ADS and LIS3DH
  spi.setMode(DSPI_MODE0);  // default to SD card mode!

  Serial0.begin(115200);
}

void loop() {
  if (millis() > lastPacketSent + packetSendIntervalMs) {
    if (streaming) {
      flushbufToSpi();
    }
    lastPacketSent = millis();
  }


  // Check serial 0 for new data
  if (Serial0.available()) {
    // Read one char from the serial 0 port
    char newChar = Serial0.read();

    switch (newChar) {
      case 'b':
        streaming = true;
        Serial0.println("starting stream");
        break;
      case 's':
        streaming = false;
        Serial0.println("stopping stream");
        break;
      case 'w':
          wifi = !wifi;
          if (wifi) {
            Serial0.println("enabled wifi mode");
          } else {
            Serial0.println("disabled wifi mode");
          }
          break;
      case '0':
        digitalWrite(WIFI_SS,LOW);
        Serial0.println("forced pin 13 to low");
        break;
      case '1':
        digitalWrite(WIFI_SS,HIGH);
        Serial0.println("forced pin 13 to high");
        break;
      default:
        Serial0.print("Sup? Dis char i don't get... ");
        Serial0.println(newChar);
        break;
    }
  }
}

void flushbufToSpi() {
  uint8_t i = 0;
  uint8_t len = packetSize;
  if (wifi) digitalWrite(WIFI_SS,LOW);
  spi.transfer(0x02);
  spi.transfer(0x00);
  while(i < packetSize) {
      spi.transfer('a');
      i++;
  }
  if (wifi) digitalWrite(WIFI_SS,HIGH);
}
