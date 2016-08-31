/*
insert header here

*/
#ifndef _____OpenBCI_32bit__
#define _____OpenBCI_32bit__


#include <DSPI.h>
#include <Arduino.h>
#include "OpenBCI_32bit_Library_Definitions.h"

void __USER_ISR ADS_DRDY_Service(void);
class OpenBCI_32bit_Library {

public:
  // ENUMS
  typedef enum ACCEL_MODE {
    ACCEL_MODE_ACTIVE,
    ACCEL_MODE_OFF
  };

  typedef enum BOARD_MODE {
    BOARD_MODE_DEFAULT,
    BOARD_MODE_DEBUG
  };

  typedef enum PACKET_TYPE {
    PACKET_TYPE_ACCEL,
    PACKET_TYPE_RAW_AUX,
    PACKET_TYPE_USER_DEFINED,
    PACKET_TYPE_ACCEL_TIME_SET,
    PACKET_TYPE_ACCEL_TIME_SYNC,
    PACKET_TYPE_RAW_AUX_TIME_SET,
    PACKET_TYPE_RAW_AUX_TIME_SYNC
  };

  typedef enum SERIAL_STATE {
    SERIAL_STATE_NONE,
    SERIAL_STATE_ONLY_SERIAL_0,
    SERIAL_STATE_ONLY_SERIAL_1,
    SERIAL_STATE_BOTH
  };

  typedef enum SPI_STATE {
    SPI_STATE_NONE,
    SPI_STATE_ONLY_TX,
    SPI_STATE_DUPLEX
  };

  typedef enum SAMPLE_RATE {
    SAMPLE_RATE_16000,
    SAMPLE_RATE_8000,
    SAMPLE_RATE_4000,
    SAMPLE_RATE_2000,
    SAMPLE_RATE_1000,
    SAMPLE_RATE_500,
    SAMPLE_RATE_250
  };

  // STRUCTS
  typedef struct {
      uint32_t  baudRate;
      boolean   active;
      boolean   rx;
      boolean   tx;
  } SerialInfo;

  typedef struct {
      boolean   active;
      boolean   rx;
      boolean   tx;
  } WifiInfo;

  // Start up functions
  OpenBCI_32bit_Library();
  boolean accelHasNewData(void);
  void    accelUpdateAxisData(void);
  void    accelWriteAxisData(void);
  void    activateAllChannelsToTestCondition(byte testInputCode, byte amplitudeCode, byte freqCode);
  void    activateChannel(byte);                  // enable the selected channel
  void    ADS_writeChannelData(void);
  void    ADS_writeChannelDataGZLL(void);
  void    ADS_writeChannelDataHighSpeed(void);
  void    ADS_writeChannelDataSpi(void);
  void    attachDaisy(void);
  void    begin(void);
  void    beginDebug(void);
  void    beginSerial1(void);
  void    beginSerial1(uint32_t);
  boolean boardBegin(void);
  boolean boardBeginDebug(void);
  boolean boardBeginDebug(int);
  void    boardReset(void);
  void    changeChannelLeadOffDetect();
  void    changeChannelLeadOffDetect(byte N);
  void    channelSettingsArraySetForAll(void);
  void    channelSettingsArraySetForChannel(byte N);
  void    channelSettingsSetForChannel(byte, byte, byte, byte, byte, byte, byte);
  void    configureInternalTestSignal(byte,byte);
  void    configureLeadOffDetection(byte, byte);
  void    deactivateChannel(byte);                // disable given channel 1-8(16)
  char    getChannelCommandForAsciiChar(char);
  char    getCharSerial0(void);
  char    getCharSerial1(void);
  char    getConstrainedChannelNumber(byte channelNumber);
  byte    getDefaultChannelSettingForSetting(byte setting);
  char    getDefaultChannelSettingForSettingAscii(byte setting);
  char    getGainForAsciiChar(char asciiChar);
  char    getNumberForAsciiChar(char asciiChar);
  char    getTargetSSForConstrainedChannelNumber(byte channelNumber);
  char    getYesOrNoForAsciiChar(char asciiChar);
  boolean hasDataSerial0(void);
  boolean hasDataSerial1(void);
  boolean isADSDataAvailable(void);
  boolean isProcessingMultibyteMsg(void);
  boolean isValidBoardType(char c);
  void    leadOffConfigureSignalForAll(byte amplitudeCode, byte freqCode);
  void    leadOffConfigureSignalForTargetSS(byte targetSS, byte amplitudeCode, byte freqCode);
  void    leadOffSetForAllChannels(void);
  void    leadOffSetForChannel(byte channelNumber, byte pInput, byte nInput);
  void    ledFlash(int numberOfFlashes);
  void    printADSregisters(int);
  void    printAllRegisters(void);
  void    printHex(byte);            // used for verbosity
  void    printRegisterName(byte);   // used for verbosity
  boolean processChar(char character);
  void    processIncomingBoardMode(char character);
  void    processIncomingSampleRate(char character);
  void    processIncomingChannelSettings(char character);
  void    processIncomingLeadOffSettings(char character);
  void    reportDefaultChannelSettings(void);
  void    removeDaisy(void);
  void    resetADS(int);     // reset all the ADS1299's settings
  void    resetChannelSettingsArrayToDefault(byte channelSettingsArray[][OPENBCI_NUMBER_OF_CHANNEL_SETTINGS]);
  void    resetLeadOffArrayToDefault(byte leadOffArray[][OPENBCI_NUMBER_OF_LEAD_OFF_SETTINGS]);
  void    startADS(void);
  void    stopADS(void);
  void    sendChannelData(void); // send the current data with sample number
  void    sendChannelDataWithAccel(void);
  void    sendChannelDataWithRawAux(void);
  void    sendChannelDataWithTimeAndAccel(void);
  void    sendChannelDataWithTimeAndRawAux(void);
  void    setChannelsToDefault(void);
  void    sendEOT(void);
  boolean smellDaisy(void);
  void    streamSafeChannelDeactivate(byte channelNumber);
  void    streamSafeChannelActivate(byte channelNumber);
  void    streamSafeChannelSettingsForChannel(byte channelNumber, byte powerDown, byte gain, byte inputType, byte bias, byte srb2, byte srb1);
  void    streamSafeSetAllChannelsToDefault(void);
  void    streamSafeReportAllChannelDefaults(void);
  void    streamSafeLeadOffSetForChannel(byte channelNumber, byte pInput, byte nInput);
  void    streamSafeTimeSendSyncSetPacket(void);
  void    streamStart(void);
  void    streamStop(void);
  void    updateBoardData(void);
  void    updateBoardDataGZLL(void);
  void    updateBoardDataHighSpeed(void);
  void    updateChannelData(void);   // retrieve data from ADS
  void    updateChannelDataGZLL(void);   // retrieve data from ADS
  void    updateChannelDataHighSpeed(void);   // retrieve data from ADS
  void    updateDaisyData(void);
  void    updateDaisyDataGZLL(void);
  void    updateDaisyDataHighSpeed(void);
  boolean waitForNewChannelData(void);
  void    write(char);
  void    write(uint8_t);
  void    write(char[] c, int len) {
  void    write(uint8_t[] b, int len)
  void    writeAuxData(void);
  void    writeChannelSettings();
  void    writeChannelSettings(byte N);
  void    writeSerial(char c);
  void    writeSerial(char[] c, int len);
  void    writeSpi(uint8_t b);
  void    writeSpi(uint8_t[] b, int len);
  void    writeTimeCurrent(void);
  void    writeZeroAux(void);

  // Variables
  boolean boardUseSRB1;             // used to keep track of if we are using SRB1
  boolean daisyPresent;
  boolean daisyUseSRB1;
  boolean streaming;
  boolean timeSynced;
  boolean useAccel;
  boolean useAux;
  boolean useInBias[OPENBCI_NUMBER_OF_CHANNELS_DAISY];        // used to remember if we were included in Bias before channel power down
  boolean useSRB2[OPENBCI_NUMBER_OF_CHANNELS_DAISY];
  boolean verbosity; // turn on/off Serial verbosity

  byte boardChannelDataRaw[24];    // array to hold raw channel data
  byte channelSettings[OPENBCI_NUMBER_OF_CHANNELS_DAISY][OPENBCI_NUMBER_OF_CHANNEL_SETTINGS];  // array to hold current channel settings
  byte daisyChannelDataRaw[24];
  byte defaultChannelSettings[OPENBCI_NUMBER_OF_CHANNEL_SETTINGS];  // default channel settings
  byte lastBoardDataRaw[24];
  byte lastDaisyDataRaw[24];
  byte leadOffSettings[OPENBCI_NUMBER_OF_CHANNELS_DAISY][OPENBCI_NUMBER_OF_LEAD_OFF_SETTINGS];  // used to control on/off of impedance measure for P and N side of each channel
  byte meanBoardDataRaw[24];
  byte meanDaisyDataRaw[24];
  byte sampleCounter;

  int boardChannelDataInt[8];    // array used when reading channel data as ints
  int daisyChannelDataInt[8];    // array used when reading channel data as ints
  int lastBoardChannelDataInt[8];
  int lastDaisyChannelDataInt[8];
  int meanBoardChannelDataInt[8];
  int meanDaisyChannelDataInt[8];
  int numChannels;

  short auxData[3]; // This is user faceing
  short axisData[3];

  uint8_t spiBuffer[255];
  uint8_t spiBufferPosition;

  uint32_t curExternBaudRate;

  volatile boolean channelDataAvailable;

  // ENUMS
  ACCEL_MODE curAccelMode;
  BOARD_MODE curBoardMode;
  PACKET_TYPE curPacketType;
  SAMPLE_RATE curSampleRate;
  SERIAL_STATE curSerialState;
  SPI_STATE curSpiState;

  // STRUCTS
  SerialInfo serial0;
  SerialInfo serial1;
  WifiInfo wifi;

  // Class Objects
  DSPI0 spi;  // use DSPI library

private:

  byte    ADS_getDeviceID(int);
  void    changeInputType(byte);
  void    csLow(int);
  void    csHigh(int);
  void    disable_accel(void); // stop data acquisition and go into low power mode
  void    enable_accel(byte);  // start acceleromoeter with default settings
  int     getX(void);
  int     getY(void);
  int     getZ(void);
  void    initialize(void);
  void    initialize_accel(byte);    // initialize
  void    initialize_ads(void);
  void    initializeSerialInfo(SerialInfo si);
  void    initializeVariables(void);
  void    initializeWifiInfo(WifiInfo wi);
  byte    LIS3DH_getDeviceID(void);
  byte    LIS3DH_read(byte);     // read a register on LIS3DH
  int     LIS3DH_read16(byte);    // read two bytes, used to get axis data
  void    LIS3DH_write(byte,byte);   // write a register on LIS3DH
  boolean LIS3DH_DataReady(void); // check LIS3DH_DRDY pin
  boolean LIS3DH_DataAvailable(void); // check LIS3DH STATUS_REG2
  void    LIS3DH_readAllRegs(void);
  void    LIS3DH_writeAxisData(void);
  void    LIS3DH_writeAxisDataForAxis(uint8_t axis);
  void    LIS3DH_updateAxisData(void);
  void    RDATA(int);   // read data one-shot
  void    RDATAC(int);  // go into read data continuous mode
  void    RESET(int);   // set all register values to default
  byte    RREG(byte,int);            // read one ADS register
  void    RREGS(byte,byte,int);      // read multiple ADS registers
  void    SDATAC(int);  // get out of read data continuous mode
  void    STANDBY(int); // go into low power mode
  void    START(int);   // start data acquisition
  void    STOP(int);    // stop data acquisition
  void    WAKEUP(int);  // get out of low power mode
  void    WREG(byte,byte,int);       // write one ADS register
  void    WREGS(byte,byte,int);      // write multiple ADS registers
  byte    xfer(byte);        // SPI Transfer function

  // Variables
  boolean isProcessingIncomingSettingsChannel;
  boolean isProcessingIncomingSettingsLeadOff;
  boolean isProcessingIncomingSerialPassThru;
  boolean isRunning;
  boolean sendTimeSyncUpPacket;
  boolean settingBoardMode;
  boolean settingSampleRate;
  byte    regData[24]; // array is used to mirror register data
  char    buffer[1];
  char    currentChannelSetting;
  char    optionalArgBuffer5[5];
  char    optionalArgBuffer6[6];
  char    optionalArgBuffer7[7];
  char    streamPacketType;
  int     boardStat; // used to hold the status register
  int     daisyStat;
  int     DRDYpinValue;
  int     lastDRDYpinValue;
  int     numberOfIncomingSettingsProcessedChannel;
  int     numberOfIncomingSettingsProcessedLeadOff;
  int     numberOfIncomingSettingsProcessedBoardType;
  uint8_t optionalArgCounter;
  unsigned long timeOfLastRead;
  boolean firstDataPacket;

};

// This let's us call into the class from within the library if necessary
extern OpenBCI_32bit_Library board;

#endif
