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
    ACCEL_MODE_ON,
    ACCEL_MODE_OFF
  };

  typedef enum TIME_SYNC_MODE {
    TIME_SYNC_MODE_ON,
    TIME_SYNC_MODE_OFF
  };

  typedef enum BOARD_MODE {
    BOARD_MODE_DEFAULT,
    BOARD_MODE_DEBUG,
    BOARD_MODE_ANALOG,
    BOARD_MODE_DIGITAL
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
      boolean   rx;
      boolean   tx;
  } SerialInfo;

  typedef struct {
      boolean   rx;
      boolean   tx;
  } SpiInfo;

  // Start up functions
  OpenBCI_32bit_Library();
  boolean accelHasNewData(void);
  void    accelUpdateAxisData(void);
  void    accelWriteAxisDataSerial(void);
  void    accelWriteAxisDataWifi(void);
  void    activateAllChannelsToTestCondition(byte testInputCode, byte amplitudeCode, byte freqCode);
  void    activateChannel(byte);                  // enable the selected channel
  void    ADS_writeChannelData(void);
  void    ADS_writeChannelDataAvgDaisy(void);
  void    ADS_writeChannelDataNoAvgDaisy(void);
  void    ADS_writeChannelDataWifi(boolean daisy);
  void    attachDaisy(void);
  void    begin(void);
  void    beginDebug(void);
  void    beginDebug(uint32_t);
  void    beginSerial1(void);
  void    beginSerial1(uint32_t);
  void    boardReset(void);
  void    changeChannelLeadOffDetect();
  void    changeChannelLeadOffDetect(byte N);
  void    channelSettingsArraySetForAll(void);
  void    channelSettingsArraySetForChannel(byte N);
  void    channelSettingsSetForChannel(byte, byte, byte, byte, byte, byte, byte);
  void    csLow(int);
  void    csHigh(int);
  void    configureInternalTestSignal(byte,byte);
  void    configureLeadOffDetection(byte, byte);
  void    deactivateChannel(byte);                // disable given channel 1-8(16)
  void    disable_accel(void); // stop data acquisition and go into low power mode
  void    enable_accel(byte);  // start acceleromoeter with default settings
  char    getChannelCommandForAsciiChar(char);
  char    getCharSerial0(void);
  char    getCharSerial1(void);
  char    getConstrainedChannelNumber(byte);
  byte    getDefaultChannelSettingForSetting(byte);
  char    getDefaultChannelSettingForSettingAscii(byte);
  char    getGainForAsciiChar(char);
  char    getNumberForAsciiChar(char);
  char    getTargetSSForConstrainedChannelNumber(byte);
  char    getYesOrNoForAsciiChar(char);
  boolean hasDataSerial0(void);
  boolean hasDataSerial1(void);
  boolean isADSDataAvailable(void);
  boolean isProcessingMultibyteMsg(void);
  void    leadOffConfigureSignalForAll(byte, byte);
  void    leadOffConfigureSignalForTargetSS(byte, byte, byte);
  void    leadOffSetForAllChannels(void);
  void    leadOffSetForChannel(byte, byte, byte);
  void    ledFlash(int);
  void    loop(void);
  void    printBoardMode(void);
  void    printSerial(uint8_t);
  void    printSerial(uint8_t c, uint8_t arg);
  void    printSerial(uint8_t *, size_t len);
  void    printSerial(const char *data) {
    printSerial((uint8_t *)data, strlen(data));
  }
  void    printlnSerial(uint8_t);
  void    printlnSerial(uint8_t c, uint8_t arg);
  void    printlnSerial(uint8_t *, size_t len);
  void    printlnSerial(const char *data) {
    printlnSerial((uint8_t *)data, strlen(data));
  }
  boolean processChar(char);
  void    processIncomingBoardMode(char);
  void    processIncomingSampleRate(char);
  void    processIncomingChannelSettings(char);
  void    processIncomingLeadOffSettings(char);
  void    reportDefaultChannelSettings(void);
  void    removeDaisy(void);
  void    resetADS(int);     // reset all the ADS1299's settings
  void    resetChannelSettingsArrayToDefault(byte channelSettingsArray[][OPENBCI_NUMBER_OF_CHANNEL_SETTINGS]);
  void    resetLeadOffArrayToDefault(byte leadOffArray[][OPENBCI_NUMBER_OF_LEAD_OFF_SETTINGS]);
  void    startADS(void);
  void    stopADS(void);
  void    sendChannelData(void);
  void    sendChannelData(PACKET_TYPE);
  void    setBoardMode(uint8_t);
  void    setChannelsToDefault(void);
  void    setCurPacketType(void);
  void    setSampleRate(uint8_t newSampleRateCode);
  void    sendEOT(void);
  void    setSerialInfo(SerialInfo, boolean, boolean, uint32_t);
  boolean smellDaisy(void);
  void    streamSafeChannelDeactivate(byte);
  void    streamSafeChannelActivate(byte);
  void    streamSafeChannelSettingsForChannel(byte, byte, byte, byte, byte, byte, byte);
  void    streamSafeSetAllChannelsToDefault(void);
  void    streamSafeReportAllChannelDefaults(void);
  void    streamSafeLeadOffSetForChannel(byte, byte, byte);
  void    streamSafeTimeSendSyncSetPacket(void);
  void    streamStart(void);
  void    streamStop(void);
  void    updateBoardData(void);
  void    updateBoardData(boolean);
  void    updateChannelData(void);   // retrieve data from ADS
  void    updateDaisyData(void);
  void    updateDaisyData(boolean);
  void    useAccel(boolean);
  void    useTimeStamp(boolean);
  void    wifiAttach(void);
  void    wifiSetInfo(SpiInfo, boolean, boolean);
  boolean wifiStoreByte(uint8_t);
  void    wifiFlushBuffer(void);
  void    wifiReadData(void);
  uint32_t wifiReadStatus(void);
  void    wifiRemove(void);
  void    wifiReset(void);
  void    wifiSendStringMulti(const char *);
  void    wifiSendStringLast(const char *);
  boolean wifiSmell(void);
  void    wifiWriteData(uint8_t *, size_t);
  void    write(uint8_t);
  void    writeAuxDataSerial(void);
  void    writeAuxDataWifi(void);
  void    writeChannelSettings(void);
  void    writeChannelSettings(byte);
  void    writeSerial(uint8_t);
  void    writeSpi(uint8_t);
  void    writeTimeCurrent(void);
  void    writeTimeCurrentSerial(uint32_t newTime);
  void    writeTimeCurrentWifi(uint32_t newTime);
  void    writeZeroAux(void);
  void    zeroAuxData(void);

  // Variables
  boolean boardUseSRB1;             // used to keep track of if we are using SRB1
  boolean daisyPresent;
  boolean daisyUseSRB1;
  boolean streaming;
  boolean useInBias[OPENBCI_NUMBER_OF_CHANNELS_DAISY];        // used to remember if we were included in Bias before channel power down
  boolean useSRB2[OPENBCI_NUMBER_OF_CHANNELS_DAISY];
  boolean verbosity; // turn on/off Serial verbosity
  boolean wifiPresent;

  byte boardChannelDataRaw[OPENBCI_NUMBER_BYTES_PER_ADS_SAMPLE];    // array to hold raw channel data
  byte channelSettings[OPENBCI_NUMBER_OF_CHANNELS_DAISY][OPENBCI_NUMBER_OF_CHANNEL_SETTINGS];  // array to hold current channel settings
  byte daisyChannelDataRaw[OPENBCI_NUMBER_BYTES_PER_ADS_SAMPLE];
  byte defaultChannelSettings[OPENBCI_NUMBER_OF_CHANNEL_SETTINGS];  // default channel settings
  byte lastBoardDataRaw[OPENBCI_NUMBER_BYTES_PER_ADS_SAMPLE];
  byte lastDaisyDataRaw[OPENBCI_NUMBER_BYTES_PER_ADS_SAMPLE];
  byte leadOffSettings[OPENBCI_NUMBER_OF_CHANNELS_DAISY][OPENBCI_NUMBER_OF_LEAD_OFF_SETTINGS];  // used to control on/off of impedance measure for P and N side of each channel
  byte meanBoardDataRaw[OPENBCI_NUMBER_BYTES_PER_ADS_SAMPLE];
  byte meanDaisyDataRaw[OPENBCI_NUMBER_BYTES_PER_ADS_SAMPLE];
  byte sampleCounter;

  int boardChannelDataInt[OPENBCI_NUMBER_CHANNELS_PER_ADS_SAMPLE];    // array used when reading channel data as ints
  int daisyChannelDataInt[OPENBCI_NUMBER_CHANNELS_PER_ADS_SAMPLE];    // array used when reading channel data as ints
  int lastBoardChannelDataInt[OPENBCI_NUMBER_CHANNELS_PER_ADS_SAMPLE];
  int lastDaisyChannelDataInt[OPENBCI_NUMBER_CHANNELS_PER_ADS_SAMPLE];
  int meanBoardChannelDataInt[OPENBCI_NUMBER_CHANNELS_PER_ADS_SAMPLE];
  int meanDaisyChannelDataInt[OPENBCI_NUMBER_CHANNELS_PER_ADS_SAMPLE];
  int numChannels;

  short auxData[3]; // This is user faceing
  short axisData[3];

  uint8_t wifiBuffer[WIFI_SPI_MAX_PACKET_SIZE];
  char wifiBufferInput[WIFI_SPI_MAX_PACKET_SIZE];
  uint8_t wifiBufferPosition;

  unsigned long lastSampleTime;

  volatile boolean channelDataAvailable;

  // ENUMS
  ACCEL_MODE curAccelMode;
  BOARD_MODE curBoardMode;
  PACKET_TYPE curPacketType;
  SAMPLE_RATE curSampleRate;
  TIME_SYNC_MODE curTimeSyncMode;

  // STRUCTS
  SerialInfo iSerial0;
  SerialInfo iSerial1;
  SpiInfo iWifi;

  // Class Objects
  DSPI0 spi;  // use DSPI library

private:

  byte    ADS_getDeviceID(int);
  void    boardBeginADSInterrupt(void);
  boolean boardBegin(void);
  boolean boardBeginDebug(void);
  boolean boardBeginDebug(uint8_t);
  void    changeInputType(byte);
  int     getX(void);
  int     getY(void);
  int     getZ(void);
  void    initialize(void);
  void    initialize_accel(byte);    // initialize
  void    initialize_ads(void);
  void    initializeSerialInfo(SerialInfo);
  void    initializeVariables(void);
  void    initializeSpiInfo(SpiInfo);
  byte    LIS3DH_getDeviceID(void);
  byte    LIS3DH_read(byte);     // read a register on LIS3DH
  int     LIS3DH_read16(byte);    // read two bytes, used to get axis data
  void    LIS3DH_write(byte,byte);   // write a register on LIS3DH
  boolean LIS3DH_DataReady(void); // check LIS3DH_DRDY pin
  boolean LIS3DH_DataAvailable(void); // check LIS3DH STATUS_REG2
  void    LIS3DH_readAllRegs(void);
  void    LIS3DH_writeAxisDataSerial(void);
  void    LIS3DH_writeAxisDataWifi(void);
  void    LIS3DH_writeAxisDataForAxisSerial(uint8_t);
  void    LIS3DH_writeAxisDataForAxisWifi(uint8_t);
  void    LIS3DH_updateAxisData(void);
  void    LIS3DH_zeroAxisData(void);
  void    printADSregisters(int);
  void    printAllRegisters(void);
  void    printFailure();
  void    printHex(byte);
  void    printRegisterName(byte);
  void    printSampleRate(void);
  void    printSuccess();
  void    processCharWifi(uint8_t);
  void    RDATA(int);   // read data one-shot
  void    RDATAC(int);  // go into read data continuous mode
  void    RESET(int);   // set all register values to default
  byte    RREG(byte,int);            // read one ADS register
  void    RREGS(byte,byte,int);      // read multiple ADS registers
  void    SDATAC(int);  // get out of read data continuous mode
  void    sendChannelDataSerial(PACKET_TYPE);
  void    sendChannelDataWifi(PACKET_TYPE, boolean);
  void    sendRawAuxWifi(void);
  void    sendTimeWithAccelWifi(void);
  void    sendTimeWithAccelSerial(void);
  void    sendTimeWithRawAuxSerial(void);
  void    sendTimeWithRawAuxWifi(void);
  void    STANDBY(int); // go into low power mode
  void    START(int);   // start data acquisition
  void    STOP(int);    // stop data acquisition
  void    WAKEUP(int);  // get out of low power mode
  void    WREG(byte,byte,int);       // write one ADS register
  void    WREGS(byte,byte,int);      // write multiple ADS registers
  byte    xfer(byte);        // SPI Transfer function

  // Variables
  boolean firstDataPacket;
  boolean isProcessingIncomingSettingsChannel;
  boolean isProcessingIncomingSettingsLeadOff;
  boolean isProcessingIncomingSerialPassThru;
  boolean isRunning;
  boolean settingBoardMode;
  boolean settingSampleRate;
  boolean toggleWifiCS;
  boolean toggleWifiReset;
  boolean soughtWifiShield;
  boolean seekingWifi;
  byte    regData[24]; // array is used to mirror register data
  char    buffer[1];
  char    currentChannelSetting;
  char    optionalArgBuffer5[5];
  char    optionalArgBuffer6[6];
  char    optionalArgBuffer7[7];
  int     boardStat; // used to hold the status register
  int     daisyStat;
  int     DRDYpinValue;
  int     lastDRDYpinValue;
  int     numberOfIncomingSettingsProcessedChannel;
  int     numberOfIncomingSettingsProcessedLeadOff;
  int     numberOfIncomingSettingsProcessedBoardType;
  uint8_t optionalArgCounter;
  unsigned long timeOfLastRead;
  unsigned long timeOfWifiToggle;
  unsigned long timeOfWifiStart;
};

// This let's us call into the class from within the library if necessary
extern OpenBCI_32bit_Library board;

#endif
