/*
 *  Built by Joel Murphy from code made by Push The World LLC based on code made for OpenBCI by Joel, Conor, Luke, and Leif.
 *
 */


#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

//    Pulse Sensor Stuff
//------------------------------------------------------------------------------
int pulsePin = A7;                // Pulse Sensor purple wire connected to pin D13 (A7)
int BPM;                   // int that holds raw Analog in 0. updated every 2mS
int Signal;                // holds the incoming raw data
int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
boolean QS = false;        // becomes true when Arduoino finds a beat.
int rate[10];                    // array to hold last ten IBI values
unsigned long pulseTimer = 0;          // used to determine pulse timing
byte pulseSampleCounter = 0;
unsigned long lastBeatTime = 0;           // used to find IBI
int P =512;                      // used to find peak in pulse wave, seeded
int T = 512;                     // used to find trough in pulse wave, seeded
int thresh = 525;                // used to find instant moment of heart beat, seeded
int amp = 100;                   // used to hold amplitude of pulse waveform, seeded
boolean firstBeat = true;        // used to seed rate array so we startup with reasonable BPM
boolean secondBeat = false;      // used to seed rate array so we startup with reasonable BPM
int noise = 75;
//------------------------------------------------------------------------------


void setup() {
  // Bring up the OpenBCI Board
  board.begin();

  // Notify the board we want to use aux data, this effects `::sendChannelData()`
  board.useAccel(false);

  // make an 'I'm alive' blink
  for(int i=0; i<3; i++){
    digitalWrite(OPENBCI_PIN_LED,LOW); delay(100);
    digitalWrite(OPENBCI_PIN_LED,HIGH); delay(200);
  }
  digitalWrite(OPENBCI_PIN_LED,LOW);
}

void loop() {
  // The main dependency of this single threaded microcontroller is to
  //  stream data from the ADS.
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();

      // Read from the PulseSensor and store auxilary position 0
      // take a reading from the ADC. Result range from 0 to 1023
      getPulse();

      // Send standard packet with channel data and accel data
      //  includes aux data because we set told the board to add it
      board.sendChannelData();
    }
  }
  // Check the serial ports for new data
  if (board.hasDataSerial0()) board.processChar(board.getCharSerial0());
  if (board.hasDataSerial1()) board.processChar(board.getCharSerial1());
  board.loop();
}
