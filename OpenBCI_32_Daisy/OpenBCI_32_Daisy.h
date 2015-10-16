/*
   insert header here

*/
#ifndef _____OpenBCI_32_Daisy__
#define _____OpenBCI_32_Daisy__


#include <DSPI.h>
#include <WProgram.h>
#include "Definitions_32_Daisy.h"

class OpenBCI_32_Daisy {
public:
    DSPI0 spi;  // use DSPI library

// BOARD 
    boolean useAccel;
    boolean useAux;
    void initialize(void);  // ADD DAISY USE outputType
    void printAllRegisters(void);   // ADD DAISY USE outputType
    void sendChannelData(void); // send the current data with sample number
    void startStreaming(void);  // ADD DAISY USE outputType
    void stopStreaming(void);   // ADD DAISY USE outputType

// ADS1299  
    void initialize_ads(void);
    void updateChannelSettings(void);
    void writeChannelSettings(void);
    void writeChannelSettings(byte);
    void setChannelsToDefault(void);
    void setChannelsToEMG(void);
    void setChannelsToECG(void);
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
    void configureLeadOffDetection(byte,byte);
    void changeChannelLeadOffDetect(void);
    void changeChannelLeadOffDetect(byte);
    void configureInternalTestSignal(byte,byte); 
    void changeInputType(byte); 
    boolean isDataAvailable(void);
    void ADS_writeChannelData(void);
    // void ADS_printDeviceID(int);   // 
    boolean smellDaisy(void);
    void removeDaisy(void);
    void attachDaisy(void);
    void writeAuxData(void);

    short auxData[3];
    byte regData[24];          // array is used to mirror register data
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
    byte channelSettings[16][6];  // array to hold current channel settings
    byte defaultChannelSettings[6];  // default channel settings
    byte leadOffSettings[16][2];  // used to control on/off of impedance measure for P and N side of each channel
    boolean useInBias[16];        // used to remember if we were included in Bias before channel power down
    boolean useSRB2[16];
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
    void LIS3DH_updateAxisData(void);

    void csLow(int);
    void csHigh(int);


private:
// ADS1299
    boolean isRunning;  
// LIS3DH
    int DRDYpinValue;
    int lastDRDYpinValue;

};

#endif
