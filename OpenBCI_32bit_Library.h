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

    // Start up functions
    OpenBCI_32bit_Library();
    boolean accelHasNewData(void);
    void    accelUpdateAxisData(void);
    void    accelWriteAxisData(void);
    void    begin(void);
    void    beginDebug(void);
    void    beginSerial1(void);
    void    beginSerial1(uint32_t);
    char    getCharSerial0(void);
    char    getCharSerial1(void);
    boolean hasDataSerial0(void);
    boolean hasDataSerial1(void);


    void    writeSerial(char *data, int len);

    boolean isADSDataAvailable(void);



    void writeTimeCurrent(void);
    void writeZeroAux(void);
    void activateAllChannelsToTestCondition(byte testInputCode, byte amplitudeCode, byte freqCode);

    void channelSettingsArraySetForAll(void);
    void channelSettingsArraySetForChannel(byte N);
    void channelSettingsSetForChannel(byte channelNumber, byte powerDown, byte gain, byte inputType, byte bias, byte srb2, byte srb1);

    void leadOffConfigureSignalForAll(byte amplitudeCode, byte freqCode);
    void leadOffConfigureSignalForTargetSS(byte targetSS, byte amplitudeCode, byte freqCode);

    void leadOffSetForAllChannels(void);
    void leadOffSetForChannel(byte channelNumber, byte pInput, byte nInput);

    boolean processChar(char character);
    void processIncomingBoardMode(char character);
    void processIncomingChannelSettings(char character);
    void processIncomingLeadOffSettings(char character);

    void resetChannelSettingsArrayToDefault(byte channelSettingsArray[][OPENBCI_NUMBER_OF_CHANNEL_SETTINGS]);
    void resetLeadOffArrayToDefault(byte leadOffArray[][OPENBCI_NUMBER_OF_LEAD_OFF_SETTINGS]);

    void sendChannelDataWithAccel(void);
    void sendChannelDataWithRawAux(void);
    void sendChannelDataWithTimeAndAccel(void);
    void sendChannelDataWithTimeAndRawAux(void);

    void streamSafeChannelDeactivate(byte channelNumber);
    void streamSafeChannelActivate(byte channelNumber);
    void streamSafeChannelSettingsForChannel(byte channelNumber, byte powerDown, byte gain, byte inputType, byte bias, byte srb2, byte srb1);
    void streamSafeSetAllChannelsToDefault(void);
    void streamSafeReportAllChannelDefaults(void);
    void streamSafeLeadOffSetForChannel(byte channelNumber, byte pInput, byte nInput);
    void streamSafeTimeSendSyncSetPacket(void);
    void streamStart(void);
    void streamStop(void);

    // OLD CODE REVERT
    void writeChannelSettings();
    void writeChannelSettings(byte N);
    void changeChannelLeadOffDetect();
    void changeChannelLeadOffDetect(byte N);
    void configureLeadOffDetection(byte amplitudeCode, byte freqCode);

    boolean waitForNewChannelData(void);

    // Variables
    boolean daisy;
    boolean streaming;
    boolean timeSynced;
    boolean sendTimeSyncUpPacket;
    boolean isProcessingIncomingSettingsChannel;
    boolean isProcessingIncomingSettingsLeadOff;
    boolean isProcessingIncomingSerialPassThru;
    boolean settingBoardMode;
    volatile boolean channelDataAvailable;

    boolean isProcessingMultibyteMsg(void);
    boolean isValidBoardType(char c);

    uint8_t curBoardMode;

    int numberOfIncomingSettingsProcessedChannel;
    int numberOfIncomingSettingsProcessedLeadOff;
    char streamPacketType;
    char currentChannelSetting;

    // Getters
    char getChannelCommandForAsciiChar(char asciiChar);
    char getConstrainedChannelNumber(byte channelNumber);
    byte getDefaultChannelSettingForSetting(byte setting);
    char getDefaultChannelSettingForSettingAscii(byte setting);
    char getGainForAsciiChar(char asciiChar);
    char getNumberForAsciiChar(char asciiChar);
    char getTargetSSForConstrainedChannelNumber(byte channelNumber);
    char getYesOrNoForAsciiChar(char asciiChar);

    DSPI0 spi;  // use DSPI library

// BOARD
    boolean useAccel;
    boolean useAux;
    void initialize(void);
    void initializeVariables(void);
    void printAllRegisters(void);
    void sendChannelData(void); // send the current data with sample number


// ADS1299
    void initialize_ads(void);
    void setChannelsToDefault(void);
    void reportDefaultChannelSettings(void);
    void printADSregisters(int);
    void WAKEUP(int);  // get out of low power mode
    void STANDBY(int); // go into low power mode
    void RESET(int);   // set all register values to default
    void START(int);   // start data acquisition
    void STOP(int);    // stop data acquisition
    void RDATAC(int);  // go into read data continuous mode
    void SDATAC(int);  // get out of read data continuous mode
    void RDATA(int);   // read data one-shot
    byte RREG(byte,int);            // read one ADS register
    void RREGS(byte,byte,int);      // read multiple ADS registers
    void WREG(byte,byte,int);       // write one ADS register
    void WREGS(byte,byte,int);      // write multiple ADS registers
    byte ADS_getDeviceID(int);
    void printRegisterName(byte);   // used for verbosity
    void printHex(byte);            // used for verbosity
    void updateChannelData(void);   // retrieve data from ADS
    void updateBoardData(void);
    void updateDaisyData(void);
    byte xfer(byte);        // SPI Transfer function
    void resetADS(int);     // reset all the ADS1299's settings
    void startADS(void);
    void stopADS(void);
    void activateChannel(byte);                  // enable the selected channel
    void deactivateChannel(byte);                // disable given channel 1-8(16)
    void configureInternalTestSignal(byte,byte);

    void changeInputType(byte);

    void ADS_writeChannelData(void);
    // void ADS_printDeviceID(int);   //
    boolean smellDaisy(void);
    void removeDaisy(void);
    void attachDaisy(void);
    void writeAuxData(void);
    void writeOutput(byte);

    short auxData[3];           // This is user faceing
    byte regData[24];           // array is used to mirror register data
    byte lastBoardDataRaw[24];
    byte boardChannelDataRaw[24];    // array to hold raw channel data
    byte meanBoardDataRaw[24];
    byte lastDaisyDataRaw[24];
    byte daisyChannelDataRaw[24];
    byte meanDaisyDataRaw[24];
    int boardStat;           // used to hold the status register
    int daisyStat;
    int boardChannelDataInt[8];    // array used when reading channel data as ints
    int lastBoardChannelDataInt[8];
    int meanBoardChannelDataInt[8];
    int daisyChannelDataInt[8];    // array used when reading channel data as ints
    int lastDaisyChannelDataInt[8];
    int meanDaisyChannelDataInt[8];
    int numChannels;
    byte channelSettings[OPENBCI_NUMBER_OF_CHANNELS_DAISY][OPENBCI_NUMBER_OF_CHANNEL_SETTINGS];  // array to hold current channel settings
    byte defaultChannelSettings[OPENBCI_NUMBER_OF_CHANNEL_SETTINGS];  // default channel settings
    byte leadOffSettings[OPENBCI_NUMBER_OF_CHANNELS_DAISY][OPENBCI_NUMBER_OF_LEAD_OFF_SETTINGS];  // used to control on/off of impedance measure for P and N side of each channel
    boolean useInBias[OPENBCI_NUMBER_OF_CHANNELS_DAISY];        // used to remember if we were included in Bias before channel power down
    boolean useSRB2[OPENBCI_NUMBER_OF_CHANNELS_DAISY];
    boolean boardUseSRB1;             // used to keep track of if we are using SRB1
    boolean daisyUseSRB1;
    boolean verbosity;      // turn on/off Serial verbosity
    boolean daisyPresent;
    boolean firstDataPacket;
    byte sampleCounter;

// LIS3DH
    short axisData[3];
    void initialize_accel(byte);    // initialize
    void enable_accel(byte);  // start acceleromoeter with default settings
    void disable_accel(void); // stop data acquisition and go into low power mode
    byte LIS3DH_getDeviceID(void);
    byte LIS3DH_read(byte);     // read a register on LIS3DH
    void LIS3DH_write(byte,byte);   // write a register on LIS3DH
    int LIS3DH_read16(byte);    // read two bytes, used to get axis data
    int getX(void);
    int getY(void);
    int getZ(void);
    boolean LIS3DH_DataReady(void); // check LIS3DH_DRDY pin
    boolean LIS3DH_DataAvailable(void); // check LIS3DH STATUS_REG2
    void LIS3DH_readAllRegs(void);
    void LIS3DH_writeAxisData(void);
    void LIS3DH_writeAxisDataForAxis(uint8_t axis);
    void LIS3DH_updateAxisData(void);

    void csLow(int);
    void csHigh(int);

    //
    boolean boardBegin(void);
    boolean boardBeginDebug(void);
    boolean boardBeginDebug(int);
    void boardReset(void);
    void ledFlash(int numberOfFlashes);
    void sendEOT(void);

    char buffer[1];

// ADS1299
    boolean isRunning;
// LIS3DH
    int DRDYpinValue;
    int lastDRDYpinValue;

    // Time sync Variables
    unsigned long timeOffset;
    unsigned long timeSetCharArrived;
    unsigned long timeComputer;
    unsigned long timeCurrent;
    // Time sync Methods
    // unsigned long   timeGet(void);
    // void            timeSet(char character);
    void            timeSendSyncSetPacket(void);

};

// This let's us call into the class from within the library if necessary
extern OpenBCI_32bit_Library board;

#endif
