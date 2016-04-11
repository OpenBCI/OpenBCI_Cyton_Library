
/*
OpenBCI 32bit Library
Place the containing folder into your libraries folder insdie the arduino folder in your Documents folder

This library will work with a single OpenBCI 32bit board, or
an OpenBCI 32bit board with an OpenBCI Daisy Module attached.

*/

#include "OpenBCI_32bit.h"

/***************************************************/
/** PUBLIC METHODS *********************************/
/***************************************************/
// CONSTRUCTOR
OpenBCI_32bit_Class::OpenBCI_32bit_Class() {
    boardType = OUTPUT_NOTHING;
    daisyPresent = false;
    streaming = false;
}

/**
* @description: The function the OpenBCI board will call in setup
* @author: AJ Keller (@pushtheworldllc)
*/
void OpenBCI_32bit_Class::begin(void) {
    // Bring the board up
    boardBegin() ? ledFlash(2) : ledFlash(1);

}

/**
* @description: called in every loop function
* @return: [boolean] - If there is data ready to be read
*/
boolean OpenBCI_32bit_Class::isThereSerialDataReadyToBeRead(void) {
    if (Serial0.available()) {
        return true;
    } else {
        return false;
    }
}

/**
* @description: called in every loop function, returns a char of the data if
*                 the data is not recognized
* @return: [char] - The character's not processed
*/
char OpenBCI_32bit_Class::readSerial(void) {
    if (Serial0.available()) {
        char newByte = Serial0.read();
        return processChar(newByte);
    }
}

/**
* @description Public function for sending data to the PC
* @param data [char *] - The data you want to send
* @author AJ Keller (@pushtheworldllc)
*/
void OpenBCI_32bit_Class::writeSerial(char *data, int len) {
    for (int i = 0; i < len; i++) {
        Serial0.write(data[i]);
    }
}


char processChar(char character) {
    switch (character){
        //TURN CHANNELS ON/OFF COMMANDS
        case '1':
            streamSafeChannelDeactivate(1);
            break;
        case '2':
            streamSafeChannelDeactivate(2);
            break;
        case '3':
            streamSafeChannelDeactivate(3);
            break;
        case '4':
            streamSafeChannelDeactivate(4);
            break;
        case '5':
            streamSafeChannelDeactivate(5);
            break;
        case '6':
            streamSafeChannelDeactivate(6);
            break;
        case '7':
            streamSafeChannelDeactivate(7);
            break;
        case '8':
            streamSafeChannelDeactivate(8);
            break;
        case 'q':
            streamSafeChannelDeactivate(9);
            break;
        case 'w':
            streamSafeChannelDeactivate(10);
            break;
        case 'e':
            streamSafeChannelDeactivate(11);
            break;
        case 'r':
            streamSafeChannelDeactivate(12);
            break;
        case 't':
            streamSafeChannelDeactivate(13);
            break;
        case 'y':
            streamSafeChannelDeactivate(14);
            break;
        case 'u':
            streamSafeChannelDeactivate(15);
            break;
        case 'i':
            streamSafeChannelDeactivate(16);
            break;
        case '!':
            streamSafeChannelActivate(1);
            break;
        case '@':
            streamSafeChannelActivate(2);
            break;
        case '#':
            streamSafeChannelActivate(3);
            break;
        case '$':
            streamSafeChannelActivate(4);
            break;
        case '%':
            streamSafeChannelActivate(5);
            break;
        case '^':
            streamSafeChannelActivate(6);
            break;
        case '&':
            streamSafeChannelActivate(7);
            break;
        case '*':
            streamSafeChannelActivate(8);
            break;
        case 'Q':
            streamSafeChannelActivate(9);
            break;
        case 'W':
            streamSafeChannelActivate(10);
            break;
        case 'E':
            streamSafeChannelActivate(11);
            break;
        case 'R':
            streamSafeChannelActivate(12);
            break;
        case 'T':
            streamSafeChannelActivate(13);
            break;
        case 'Y':
            streamSafeChannelActivate(14);
            break;
        case 'U':
            streamSafeChannelActivate(15);
            break;
        case 'I':
            streamSafeChannelActivate(16);
            break;


        // TEST SIGNAL CONTROL COMMANDS
        case '0':
            activateAllChannelsToTestCondition(ADSINPUT_SHORTED,ADSTESTSIG_NOCHANGE,ADSTESTSIG_NOCHANGE);
            break;
        case '-':
            activateAllChannelsToTestCondition(ADSINPUT_TESTSIG,ADSTESTSIG_AMP_1X,ADSTESTSIG_PULSE_SLOW);
            break;
        case '=':
            activateAllChannelsToTestCondition(ADSINPUT_TESTSIG,ADSTESTSIG_AMP_1X,ADSTESTSIG_PULSE_FAST);
            break;
        case 'p':
            activateAllChannelsToTestCondition(ADSINPUT_TESTSIG,ADSTESTSIG_AMP_2X,ADSTESTSIG_DCSIG);
            break;
        case '[':
            activateAllChannelsToTestCondition(ADSINPUT_TESTSIG,ADSTESTSIG_AMP_2X,ADSTESTSIG_PULSE_SLOW);
            break;
        case ']':
            activateAllChannelsToTestCondition(ADSINPUT_TESTSIG,ADSTESTSIG_AMP_2X,ADSTESTSIG_PULSE_FAST);
            break;

        // SD CARD COMMANDS
        case 'A': // 5min
        case 'S': // 15min
        case 'F': // 30 min
        case 'G': // 1 hr
        case 'H': // 2 hr
        case 'J': // 4 hr
        case 'K': // 12 hr
        case 'L': // 24 hr
        case 'a': // 512 blocks
            fileSize = token;
            SDfileOpen = setupSDcard(fileSize); //
            break;
        case 'j': // close the file, if it's open
            if(SDfileOpen){
                SDfileOpen = closeSDfile();
            }
            break;

        // CHANNEL SETTING COMMANDS
        case 'x':  // expect 6 parameters
            if(!is_running) {Serial0.println("ready to accept new channel settings");}
            channelSettingsCounter = 0;
            getChannelSettings = true;
            break;
        case 'X':  // latch channel settings
            if(!is_running) {
                Serial0.println("updating channel settings");
            }
            writeChannelSettings_maintainRunningState(currentChannelToSet); break;
        case 'd':  // reset all channel settings to default
            if(!is_running) {Serial0.println("updating channel settings to default");}
            setChannelsToDefaultSetting(); break;
        case 'D':  // report the default settings
            sendDefaultChannelSettings(); break;

        // LEAD OFF IMPEDANCE DETECTION COMMANDS
        case 'z':
            processIncomingLeadOffSettings();
            break;

        // DAISY MODULE COMMANDS
        case 'c':  // use 8 channel mode
        if(OBCI.daisyPresent){ OBCI.removeDaisy(); }
        outputType = OUTPUT_8_CHAN;
        break;
        case 'C':  // use 16 channel mode
        if(OBCI.daisyPresent == false){OBCI.attachDaisy();}
        if(OBCI.daisyPresent){
            Serial0.print("16"); outputType = OUTPUT_16_CHAN;
        }else{
            Serial0.print("8"); outputType = OUTPUT_8_CHAN;
        }
        sendEOT();
        break;

        // STREAM DATA AND FILTER COMMANDS
        case 'b':  // stream data
            if(SDfileOpen) stampSD(ACTIVATE);                     // time stamp the start time
            if(OBCI.useAccel){OBCI.enable_accel(RATE_25HZ);}      // fire up the accelerometer if you want it
            startRunning(outputType);                             // turn on the fire hose
            break;
        case 's':  // stop streaming data
            if(SDfileOpen) stampSD(DEACTIVATE);       // time stamp the stop time
            if(OBCI.useAccel){OBCI.disable_accel();}  // shut down the accelerometer if you're using it
            stopRunning();
            break;
        case 'f':
        useFilters = true;
        break;
        case 'g':
        useFilters = false;
        break;

        //  INITIALIZE AND VERIFY
        case 'v':
            boardReset();  // initialize ADS and read device IDs
            break;
        //  QUERY THE ADS AND ACCEL REGITSTERS
        case '?':
            printRegisters();     // print the ADS and accelerometer register values
            break;
        default:
            return character;
    }
}





/***************************************************/
/** PRIVATE METHODS ********************************/
/***************************************************/

/**
* @description: This is a function that is called once and confiures all pins on
*                 the PIC32 uC
* @author: AJ Keller (@pushtheworldllc)
*/
boolean OpenBCI_32bit_Class::begin(void) {
    // Initalize the serial port baud rate
    Serial0.begin(OPENBCI_BAUD_RATE);

    pinMode(OPENBCI_PIN_LED, OUTPUT);
    pinMode(OPENBCI_PIN_PGC, OUTPUT);

    // Do a soft reset
    boardReset();

    return true;

}

/**
* @description: This is a function that can be called multiple times, this is
*                 what we refer to as a `soft reset`. You will hear/see this
*                 many times.
* @author: AJ Keller (@pushtheworldllc)
*/
void OpenBCI_32bit_Class::boardReset(void) {
    initialize();

    Serial0.println("OpenBCI V3 16 channel");
    configureLeadOffDetection(LOFF_MAG_6NA, LOFF_FREQ_31p2HZ);
    Serial0.print("On Board ADS1299 Device ID: 0x"); Serial0.println(ADS_getDeviceID(ON_BOARD),HEX);
    if(OBCI.daisyPresent){  // library will set this in initialize() if daisy present and functional
      Serial0.print("On Daisy ADS1299 Device ID: 0x"); Serial0.println(ADS_getDeviceID(ON_DAISY),HEX);
    }
    Serial0.print("LIS3DH Device ID: 0x"); Serial0.println(OBCI.LIS3DH_getDeviceID(),HEX);
    Serial0.print(OPENBCI_EOT);
}


void OpenBCI_32bit_Class::ledFlash(int numberOfFlashes) {
    for(int i = 0;i < numberOfFlashes; i++) {
        digitalWrite(OPENBCI_PIN_LED,HIGH);
        delay(500);
        digitalWrite(OPENBCI_PIN_LED,LOW);
        delay(500);
    }
}

/**
* @description: Simple method to send the EOT over serial...
* @author: AJ Keller (@pushtheworldllc)
*/
void OpenBCI_32bit_Class::serialWriteEOT(void) {
    Serial0.print("$$$");
}



void OpenBCI_32bit_Class::activateAllChannelsToTestCondition(byte testInputCode, byte amplitudeCode, byte freqCode)
{
    boolean wasStreaming = streaming;

    // Stop streaming if you are currently streaming
    if (streaming) {
        streamStop();
    }

    //must stop running to change channel settings
    delay(10);

    //set the test signal to the desired state
    configureInternalTestSignal(amplitudeCode,freqCode);
    //change input type settings for all channels
    changeInputType(testInputCode);

    // Restart stream if need be
    if (wasStreaming) {
        streamStart();
    }
}

/**
 * @description When a 'z' is found on the serial port, we jump to this function
 *                  where we continue to read from the serial port and read the
 *                  remaining 4 bytes.
 */
void OpenBCI_32bit_Class::processIncomingLeadOffSettings(void) {
    // we need to pull off four bytes from serial port
    unsigned long startTime = millis();

    int bytesIn = 0;

    int bytesToRead = 4; // total bytes left in to get for impedance

    char currentChannel;

    while (bytesIn < bytesToRead) {
        if (Serial0.availale()) {
            char newChar = Serial0.read();

            if (bytesIn == 0) { // This is the first byte
                currentChannel = getChannelCommandForAsciiChar(newChar);
            } else if (bytesIn == 1) {
                leadOffSettings[currentChannel][PCHAN] = getNumberForAsciiChar(newChar);
            } else if (bytesIn == 2) {
                leadOffSettings[currentChannel][NCHAN] = getNumberForAsciiChar(newChar);
            } else {
                // The forth character must be the impedance latch
                if (newChar != OPENBCI_CHANNEL_IMPEDANCE_LATCH) {
                    if (!streaming) {
                        Serial0.print("Err: 4th char not ");
                        Serial0.println(OPENBCI_CHANNEL_IMPEDANCE_LATCH);
                    }
                    return; // Exit
                } else {
                    if (!streaming) {
                        Serial0.println("All impedance recieved");
                    }
                }
            }
            bytesIn++;
        }

        // This is timeout protection, in case for some reason bytes were lost in
        //  the serial transmission
        if (millis() > (startTime + OPENBCI_TIME_OUT_MS_1)) {
            return; // return void
        }
    }

    // Set lead off settings
    streamSafeLeadOffSetForChannel(currentChannel,leadOffSettings[currentChannel][PCHAN],leadOffSettings[currentChannel][NCHAN]);
}

/**
 * @description When a 'x' is found on the serial port, we jump to this function
 *                  where we continue to read from the serial port and read the
 *                  remaining 7 bytes.
 */
void OpenBCI_32bit_Class::processIncomingChannelSettings(void) {
    // we need to pull off four bytes from serial port
    unsigned long startTime = millis();

    int bytesIn = 0;

    int bytesToRead = 7; // total bytes left in to get for impedance

    char currentChannel;

    while (bytesIn < bytesToRead) {
        if (Serial0.availale()) {
            char newChar = Serial0.read();

            if (bytesIn == 0) { // This is the first byte
                currentChannel = getChannelCommandForAsciiChar(newChar);
            } else if (bytesIn == 1) { // POWER_DOWN
                channelSettings[currentChannel][POWER_DOWN] = getNumberForAsciiChar(newChar);
            } else if (bytesIn == 2) { // GAIN_SET
                channelSettings[currentChannel][GAIN_SET] = getGainForAsciiChar(newChar);
            } else if (bytesIn == 3) { // INPUT_TYPE_SET
                channelSettings[currentChannel][INPUT_TYPE_SET] = getNumberForAsciiChar(newChar);
            } else if (bytesIn == 4) { // BIAS_SET
                channelSettings[currentChannel][BIAS_SET] = getNumberForAsciiChar(newChar);
            } else if (bytesIn == 5) { // SRB2_SET
                channelSettings[currentChannel][SRB2_SET] = getNumberForAsciiChar(newChar);
            } else if (bytesIn == 6) { // SRB1_SET
                channelSettings[currentChannel][SRB1_SET] = getNumberForAsciiChar(newChar);
            } else {
                // The forth character must be the impedance latch
                if (newChar != OPENBCI_CHANNEL_IMPEDANCE_LATCH) {
                    if (!streaming) {
                        Serial0.print("Err: 7th char not ");
                        Serial0.println(OPENBCI_CHANNEL_CMD_LATCH);
                    }
                    return; // Exit
                } else {
                    if (!streaming) {
                        Serial0.println("All character settings recieved");
                    }
                }
            }
            bytesIn++;
        }

        // This is timeout protection, in case for some reason bytes were lost in
        //  the serial transmission
        if (millis() > (startTime + OPENBCI_TIME_OUT_MS_3)) {
            return; // return void
        }
    }

    // Set channel settings
    streamSafeChannelSettingsForChannel(currentChannel + 1, channelSettings[currentChannel][POWER_DOWN], channelSettings[currentChannel][GAIN_SET], channelSettings[currentChannel][INPUT_TYPE_SET], channelSettings[currentChannel][BIAS_SET], channelSettings[currentChannel][SRB2_SET], channelSettings[currentChannel][SRB1_SET]);
}

// <<<<<<<<<<<<<<<<<<<<<<<<<  BOARD WIDE FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void OpenBCI_32bit_Class::initialize(){
    pinMode(SD_SS,OUTPUT); digitalWrite(SD_SS,HIGH);  // de-select SDcard if present
    pinMode(BOARD_ADS, OUTPUT); digitalWrite(BOARD_ADS,HIGH);
    pinMode(DAISY_ADS, OUTPUT); digitalWrite(DAISY_ADS,HIGH);
    pinMode(LIS3DH_SS,OUTPUT); digitalWrite(LIS3DH_SS,HIGH);
    spi.begin();
    spi.setSpeed(4000000);  // use 4MHz for ADS and LIS3DH
    spi.setMode(DSPI_MODE0);  // default to SD card mode!
    initialize_ads(); // hard reset ADS, set pin directions
    initialize_accel(SCALE_4G); // set pin directions, G scale, DRDY interrupt, power down
}

void OpenBCI_32bit_Class::printAllRegisters(){
    if(!isRunning){
        Serial0.println("\nBoard ADS Registers");
        printADSregisters(BOARD_ADS);
        if(daisyPresent){
            Serial0.println("\nDaisy ADS Registers");
            printADSregisters(DAISY_ADS);
        }
        Serial0.println("\nLIS3DH Registers");
        LIS3DH_readAllRegs();
    }
}

void OpenBCI_32bit_Class::sendChannelData(){
    Serial0.write(sampleCounter); // 1 byte
    ADS_writeChannelData();       // 24 bytes
    if(useAux){
        writeAuxData();             // 6 bytes of aux data
    }else if(useAccel){           // or
        LIS3DH_writeAxisData();     // 6 bytes of accelerometer data
    }else{
        byte zero = 0x00;
        for(int i=0; i<6; i++){
            Serial0.write(zero);
        }
    }
    sampleCounter++;
}



void OpenBCI_32bit_Class::writeAuxData(){
    for(int i=0; i<3; i++){
        Serial0.write(highByte(auxData[i])); // write 16 bit axis data MSB first
        Serial0.write(lowByte(auxData[i]));  // axisData is array of type short (16bit)
        auxData[i] = 0;   // reset auxData bytes to 0
    }
}

//SPI communication method
byte OpenBCI_32bit_Class::xfer(byte _data)
{
    byte inByte;
    inByte = spi.transfer(_data);
    return inByte;
}

//SPI chip select method
void OpenBCI_32bit_Class::csLow(int SS)
{ // select an SPI slave to talk to
    switch(SS){
        case BOARD_ADS:
            spi.setMode(DSPI_MODE1);
            spi.setSpeed(4000000);
            digitalWrite(BOARD_ADS, LOW);
            break;
        case LIS3DH_SS:
            spi.setMode(DSPI_MODE3);
            spi.setSpeed(4000000);
            digitalWrite(LIS3DH_SS, LOW);
            break;
        case SD_SS:
            spi.setMode(DSPI_MODE0);
            spi.setSpeed(20000000);
            digitalWrite(SD_SS, LOW);
            break;
        case DAISY_ADS:
            spi.setMode(DSPI_MODE1);
            spi.setSpeed(4000000);
            digitalWrite(DAISY_ADS, LOW);
            break;
        case BOTH_ADS:
            spi.setMode(DSPI_MODE1);
            spi.setSpeed(4000000);
            digitalWrite(BOARD_ADS,LOW);
            digitalWrite(DAISY_ADS,LOW);
            break;
        default:
            break;
    }
}

void OpenBCI_32bit_Class::csHigh(int SS)
{ // deselect SPI slave
    switch(SS){
        case BOARD_ADS:
            digitalWrite(BOARD_ADS, HIGH);
            spi.setSpeed(20000000);
            break;
        case LIS3DH_SS:
            digitalWrite(LIS3DH_SS, HIGH);
            spi.setSpeed(20000000);
            break;
        case SD_SS:
            digitalWrite(SD_SS, HIGH);
            spi.setSpeed(4000000);
            break;
        case DAISY_ADS:
            digitalWrite(DAISY_ADS, HIGH);
            spi.setSpeed(20000000);
            break;
        case BOTH_ADS:
            digitalWrite(BOARD_ADS, HIGH);
            digitalWrite(DAISY_ADS, HIGH);
            spi.setSpeed(20000000); break;
            default:
        break;
    }
    spi.setMode(DSPI_MODE0);  // DEFAULT TO SD MODE!
}

// <<<<<<<<<<<<<<<<<<<<<<<<<  END OF BOARD WIDE FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
// *************************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<  ADS1299 FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


void OpenBCI_32bit_Class::initialize_ads(){
    // recommended power up sequence requiers >Tpor (~32mS)
    delay(50);
    pinMode(ADS_RST,OUTPUT);
    digitalWrite(ADS_RST,LOW);  // reset pin connected to both ADS ICs
    delayMicroseconds(4);	// toggle reset pin
    digitalWrite(ADS_RST,HIGH); // this will reset the Daisy if it is present
    delayMicroseconds(20);	// recommended to wait 18 Tclk before using device (~8uS);
    // initalize the  data ready chip select and reset pins:
    pinMode(ADS_DRDY, INPUT); // we get DRDY asertion from the on-board ADS
    delay(40);
    resetADS(BOARD_ADS); // reset the on-board ADS registers, and stop DataContinuousMode
    delay(10);
    WREG(CONFIG1,0xB6,BOARD_ADS); // tell on-board ADS to output its clk, set the data rate to 250SPS
    delay(40);
    resetADS(DAISY_ADS); // software reset daisy module if present
    delay(10);
    daisyPresent = smellDaisy(); // check to see if daisy module is present
    if(!daisyPresent){
        WREG(CONFIG1,0x96,BOARD_ADS); // turn off clk output if no daisy present
        numChannels = 8;    // expect up to 8 ADS channels
    }else{
        numChannels = 16;   // expect up to 16 ADS channels
    }

    // DEFAULT CHANNEL SETTINGS FOR ADS
    defaultChannelSettings[POWER_DOWN] = NO;        // on = NO, off = YES
    defaultChannelSettings[GAIN_SET] = ADS_GAIN24;     // Gain setting
    defaultChannelSettings[INPUT_TYPE_SET] = ADSINPUT_NORMAL;// input muxer setting
    defaultChannelSettings[BIAS_SET] = YES;    // add this channel to bias generation
    defaultChannelSettings[SRB2_SET] = YES;       // connect this P side to SRB2
    defaultChannelSettings[SRB1_SET] = NO;        // don't use SRB1

    for(int i=0; i<numChannels; i++){
        for(int j=0; j<6; j++){
            channelSettings[i][j] = defaultChannelSettings[j];  // assign default settings
        }
        useInBias[i] = true;    // keeping track of Bias Generation
        useSRB2[i] = true;      // keeping track of SRB2 inclusion
    }
    boardUseSRB1 = daisyUseSRB1 = false;

    writeChannelSettings(); // write settings to the on-board and on-daisy ADS if present

    WREG(CONFIG3,0b11101100,BOTH_ADS); delay(1);  // enable internal reference drive and etc.
    for(int i=0; i<numChannels; i++){  // turn off the impedance measure signal
        leadOffSettings[i][PCHAN] = OFF;
        leadOffSettings[i][NCHAN] = OFF;
    }
    verbosity = false;      // when verbosity is true, there will be Serial feedback
    firstDataPacket = true;
}

//////////////////////////////////////////////
///////////// STREAM METHODS /////////////////
//////////////////////////////////////////////

/**
* @description Used to activate a channel, if running must stop and start after...
* @param channelNumber int the channel you want to change
* @author AJ Keller (@pushtheworldllc)
*/
void OpenBCI_32bit_Class::streamSafeChannelActivate(byte channelNumber) {
    boolean wasStreaming = streaming;

    // Stop streaming if you are currently streaming
    if (streaming) {
        streamStop();
    }

    // Activate the channel
    activateChannel(channelNumber);

    // Restart stream if need be
    if (wasStreaming) {
        streamStart();
    }
}

/**
* @description Used to deactivate a channel, if running must stop and start after...
* @param channelNumber int the channel you want to change
* @author AJ Keller (@pushtheworldllc)
*/
void OpenBCI_32bit_Class::streamSafeChannelDeactivate(byte channelNumber){
    boolean wasStreaming = streaming;

    // Stop streaming if you are currently streaming
    if (streaming) {
        streamStop();
    }

    // deactivate the channel
    deactivateChannel(channelNumber);

    // Restart stream if need be
    if (wasStreaming) {
        streamStart();
    }
}

/**
 * @description Used to set lead off for a channel, if running must stop and start after...
 * @param `channelNumber` - [byte] - The channel you want to change
 * @param `pInput` - [byte] - Apply signal to P input, either ON (1) or OFF (0)
 * @param `nInput` - [byte] - Apply signal to N input, either ON (1) or OFF (0)
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::streamSafeLeadOffSetForChannel(byte channelNumber, byte pInput, byte nInput) {
    boolean wasStreaming = streaming;

    // Stop streaming if you are currently streaming
    if (streaming) {
        streamStop();
    }

    leadOffSetForChannel(channelNumber, pInput, nInput);

    // Restart stream if need be
    if (wasStreaming) {
        streamStart();
    }
}

/**
 * @description Used to set lead off for a channel, if running must stop and start after...
 * @params see `.channelSettingsSetForChannel()` for parameters
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::streamSafeChannelSettingsForChannel(byte channelNumber, byte powerDown, byte gain, byte inputType, byte bias, byte srb2, byte srb1) {
    boolean wasStreaming = streaming;

    // Stop streaming if you are currently streaming
    if (streaming) {
        streamStop();
    }

    channelSettingsSetForChannel(channelNumber, powerDown, gain, inputType, bias, srb2, srb1);

    // Restart stream if need be
    if (wasStreaming) {
        streamStart();
    }
}

/**
* @description Call this to start the streaming data from the ADS1299
* @returns boolean if able to start streaming
*/
boolean OpenBCI_32bit_Class::streamStart(){  // needs daisy functionality
    if (streaming) { // already streaming...
        return false;
    } else { // not streaming, so we can start
        streaming = true;
        startADS();
        return true;
    }
}

/**
* @description Call this to stop streaming from the ADS1299
* @returns boolean if able to stop streaming
*/
boolean OpenBCI_32bit_Class::streamStop(){
    if (streaming) { // we are streaming so we can stop
        streaming = false;
        stopADS();
        return true;
    } else {
        return false;
    }
}

//////////////////////////////////////////////
////////////// DAISY METHODS /////////////////
//////////////////////////////////////////////
boolean OpenBCI_32bit_Class::smellDaisy(void){ // check if daisy present
    boolean isDaisy = false;
    byte setting = RREG(ID_REG,DAISY_ADS); // try to read the daisy product ID
    if(verbosity){Serial0.print("Daisy ID 0x"); Serial0.println(setting,HEX);}
    if(setting == ADS_ID) {isDaisy = true;} // should read as 0x3E
    return isDaisy;
}

void OpenBCI_32bit_Class::removeDaisy(void){
    if(daisyPresent){
        SDATAC(DAISY_ADS);
        RESET(DAISY_ADS);
        STANDBY(DAISY_ADS);
        daisyPresent = false;
        if(!isRunning) Serial0.println("daisy removed");
    }else{
        if(!isRunning) Serial0.println("no daisy to remove!");
    }
}

void OpenBCI_32bit_Class::attachDaisy(void){
    WREG(CONFIG1,0xB6,BOARD_ADS); // tell on-board ADS to output the clk, set the data rate to 250SPS
    delay(40);
    resetADS(DAISY_ADS); // software reset daisy module if present
    delay(10);
    daisyPresent = smellDaisy();
    if(!daisyPresent){
        WREG(CONFIG1,0x96,BOARD_ADS); // turn off clk output if no daisy present
        numChannels = 8;    // expect up to 8 ADS channels
        if(!isRunning) Serial0.println("no daisy to attach!");
    }else{
        numChannels = 16;   // expect up to 16 ADS channels
        if(!isRunning) Serial0.println("daisy attached");
    }
}

//reset all the ADS1299's settings. Stops all data acquisition
void OpenBCI_32bit_Class::resetADS(int targetSS)
{
    int startChan, stopChan;
    if(targetSS == BOARD_ADS) {startChan = 1; stopChan = 8;}
    if(targetSS == DAISY_ADS) {startChan = 9; stopChan = 16;}
    RESET(targetSS);             // send RESET command to default all registers
    SDATAC(targetSS);            // exit Read Data Continuous mode to communicate with ADS
    delay(100);
    // turn off all channels
    for (int chan=startChan; chan <= stopChan; chan++) {
        deactivateChannel(chan);
    }
}

void OpenBCI_32bit_Class::setChannelsToDefault(void){
    for(int i=0; i<numChannels; i++){
        for(int j=0; j<6; j++){
            channelSettings[i][j] = defaultChannelSettings[j];
        }
        useInBias[i] = true;    // keeping track of Bias Generation
        useSRB2[i] = true;      // keeping track of SRB2 inclusion
    }
    boardUseSRB1 = daisyUseSRB1 = false;

    writeChannelSettings();       // write settings to on-board ADS

    for(int i=0; i<numChannels; i++){   // turn off the impedance measure signal
        leadOffSettings[i][PCHAN] = OFF;
        leadOffSettings[i][NCHAN] = OFF;
    }
    changeChannelLeadOffDetect(); // write settings to all ADS


    WREG(MISC1,0x00,BOARD_ADS);  // open SRB1 switch on-board
    if(daisyPresent){ WREG(MISC1,0x00,DAISY_ADS); } // open SRB1 switch on-daisy
}


void OpenBCI_32bit_Class::reportDefaultChannelSettings(void){

    Serial0.write(defaultChannelSettings[POWER_DOWN] + '0');        // on = NO, off = YES
    Serial0.write((defaultChannelSettings[GAIN_SET] >> 4) + '0');     // Gain setting
    Serial0.write(defaultChannelSettings[INPUT_TYPE_SET] +'0');// input muxer setting
    Serial0.write(defaultChannelSettings[BIAS_SET] + '0');    // add this channel to bias generation
    Serial0.write(defaultChannelSettings[SRB2_SET] + '0');       // connect this P side to SRB2
    Serial0.write(defaultChannelSettings[SRB1_SET] + '0');        // don't use SRB1
}

// write settings for ALL 8 channels for a given ADS board
// channel settings: powerDown, gain, inputType, SRB2, SRB1
void OpenBCI_32bit_Class::writeChannelSettings(){
    boolean use_SRB1 = false;
    byte setting, startChan, endChan, targetSS;

    for(int b=0; b<2; b++){
        if(b == 0){ targetSS = BOARD_ADS; startChan = 0; endChan = 8; }
        if(b == 1){
            if(!daisyPresent){ return; }
            targetSS = DAISY_ADS; startChan = 8; endChan = 16;
        }

        SDATAC(targetSS); delay(1);      // exit Read Data Continuous mode to communicate with ADS

        for(byte i=startChan; i<endChan; i++){ // write 8 channel settings
            setting = 0x00;
            if(channelSettings[i][POWER_DOWN] == YES){setting |= 0x80;}
            setting |= channelSettings[i][GAIN_SET]; // gain
            setting |= channelSettings[i][INPUT_TYPE_SET]; // input code
            if(channelSettings[i][SRB2_SET] == YES){
                setting |= 0x08;    // close this SRB2 switch
                useSRB2[i] = true;  // remember SRB2 state for this channel
            }else{
                useSRB2[i] = false; // rememver SRB2 state for this channel
            }
            WREG(CH1SET+(i-startChan),setting,targetSS);  // write this channel's register settings

            // add or remove this channel from inclusion in BIAS generation
            setting = RREG(BIAS_SENSP,targetSS);                   //get the current P bias settings
            if(channelSettings[i][BIAS_SET] == YES){
                bitSet(setting,i-startChan); useInBias[i] = true;    //add this channel to the bias generation
            }else{
                bitClear(setting,i-startChan); useInBias[i] = false; //remove this channel from bias generation
            }
            WREG(BIAS_SENSP,setting,targetSS); delay(1);           //send the modified byte back to the ADS

            setting = RREG(BIAS_SENSN,targetSS);                   //get the current N bias settings
            if(channelSettings[i][BIAS_SET] == YES){
                bitSet(setting,i-startChan);    //set this channel's bit to add it to the bias generation
            }else{
                bitClear(setting,i-startChan);  // clear this channel's bit to remove from bias generation
            }
            WREG(BIAS_SENSN,setting,targetSS); delay(1);           //send the modified byte back to the ADS

            if(channelSettings[i][SRB1_SET] == YES){
                use_SRB1 = true;  // if any of the channel setting closes SRB1, it is closed for all
            }
        } // end of CHnSET and BIAS settings
    } // end of board select loop
    if(use_SRB1){
        for(int i=startChan; i<endChan; i++){
            channelSettings[i][SRB1_SET] = YES;
        }
        WREG(MISC1,0x20,targetSS);     // close SRB1 swtich
        if(targetSS == BOARD_ADS){ boardUseSRB1 = true; }
        if(targetSS == DAISY_ADS){ daisyUseSRB1 = true; }
    }else{
        for(int i=startChan; i<endChan; i++){
            channelSettings[i][SRB1_SET] = NO;
        }
        WREG(MISC1,0x00,targetSS);    // open SRB1 switch
        if(targetSS == BOARD_ADS){ boardUseSRB1 = false; }
        if(targetSS == DAISY_ADS){ daisyUseSRB1 = false; }
    }
}

// write settings for a SPECIFIC channel on a given ADS board
void OpenBCI_32bit_Class::writeChannelSettings(byte N){

    byte setting, startChan, endChan, targetSS;
    if(N < 9){  // channels 1-8 on board
        targetSS = BOARD_ADS; startChan = 0; endChan = 8;
    }else{      // channels 9-16 on daisy module
        if(!daisyPresent) { return; }
        targetSS = DAISY_ADS; startChan = 8; endChan = 16;
    }
    // function accepts channel 1-16, must be 0 indexed to work with array
    N = constrain(N-1,startChan,endChan-1);  //subtracts 1 so that we're counting from 0, not 1
    // first, disable any data collection
    SDATAC(targetSS); delay(1);      // exit Read Data Continuous mode to communicate with ADS

    setting = 0x00;
    if(channelSettings[N][POWER_DOWN] == YES) setting |= 0x80;
    setting |= channelSettings[N][GAIN_SET]; // gain
    setting |= channelSettings[N][INPUT_TYPE_SET]; // input code
    if(channelSettings[N][SRB2_SET] == YES){
        setting |= 0x08; // close this SRB2 switch
        useSRB2[N] = true;  // keep track of SRB2 usage
    }else{
        useSRB2[N] = false;
    }
    WREG(CH1SET+(N-startChan), setting, targetSS);  // write this channel's register settings

    // add or remove from inclusion in BIAS generation
    setting = RREG(BIAS_SENSP,targetSS);       //get the current P bias settings
    if(channelSettings[N][BIAS_SET] == YES){
        useInBias[N] = true;
        bitSet(setting,N-startChan);    //set this channel's bit to add it to the bias generation
    }else{
        useInBias[N] = false;
        bitClear(setting,N-startChan);  // clear this channel's bit to remove from bias generation
    }
    WREG(BIAS_SENSP,setting,targetSS); delay(1); //send the modified byte back to the ADS
    setting = RREG(BIAS_SENSN,targetSS);       //get the current N bias settings
    if(channelSettings[N][BIAS_SET] == YES){
        bitSet(setting,N-startChan);    //set this channel's bit to add it to the bias generation
    }else{
        bitClear(setting,N-startChan);  // clear this channel's bit to remove from bias generation
    }
    WREG(BIAS_SENSN,setting,targetSS); delay(1); //send the modified byte back to the ADS

    // if SRB1 is closed or open for one channel, it will be the same for all channels
    if(channelSettings[N][SRB1_SET] == YES){
        for(int i=startChan; i<endChan; i++){
            channelSettings[i][SRB1_SET] = YES;
        }
        if(targetSS == BOARD_ADS) boardUseSRB1 = true;
        if(targetSS == DAISY_ADS) daisyUseSRB1 = true;
        setting = 0x20;     // close SRB1 swtich
    }
    if(channelSettings[N][SRB1_SET] == NO){
        for(int i=startChan; i<endChan; i++){
            channelSettings[i][SRB1_SET] = NO;
        }
        if(targetSS == BOARD_ADS) boardUseSRB1 = false;
        if(targetSS == DAISY_ADS) daisyUseSRB1 = false;
        setting = 0x00;     // open SRB1 switch
    }
    WREG(MISC1,setting,targetSS);
}

/**
 * @description Set all channels using global channelSettings array
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::channelSettingsArraySetForAll(void) {
    byte channelNumberUpperLimit;

    // The upper limit of the channels, either 8 or 16
    channelNumberUpperLimit = daisyPresent ? OPENBCI_NUMBER_OF_CHANNELS_DAISY : OPENBCI_NUMBER_OF_CHANNELS_DEFAULT;

    // Loop through all channels
    for (int i = 1; i <= channelNumberUpperLimit; i++) {
        // contstrain the channel number to 0-15
        int index = i - 1;

        // Set for this channel
        channelSettingsSetForChannel((byte)i, channelSettings[index][POWER_DOWN], channelSettings[index][GAIN_SET], channelSettings[index][INPUT_TYPE_SET], channelSettings[index][BIAS_SET], channelSettings[index][SRB2_SET], channelSettings[index][SRB1_SET]);
    }
}

/**
 * @description Set channel using global channelSettings array for channelNumber
 * @param `channelNumber` - [byte] - 1-16 channel number
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::channelSettingsArraySetForChannel(byte channelNumber) {
    // contstrain the channel number to 0-15
    char index = getConstrainedChannelNumber(channelNumber);

    // Set for this channel
    channelSettingsSetForChannel(channelNumber, channelSettings[index][POWER_DOWN], channelSettings[index][GAIN_SET], channelSettings[index][INPUT_TYPE_SET], channelSettings[index][BIAS_SET], channelSettings[index][SRB2_SET], channelSettings[index][SRB1_SET]);
}

/**
 * @description To add a usability abstraction layer above channel setting commands. Due to the
 *          extensive and highly specific nature of the channel setting command chain.
 * @param `channelNumber` - [byte] (1-16) for index, so convert channel to array prior
 * @param `powerDown` - [byte] - YES (1) or NO (0)
 *          Powers channel down
 * @param `gain` - [byte] - Sets the gain for the channel
 *          ADS_GAIN01 (0b00000000)	// 0x00
 *          ADS_GAIN02 (0b00010000)	// 0x10
 *          ADS_GAIN04 (0b00100000)	// 0x20
 *          ADS_GAIN06 (0b00110000)	// 0x30
 *          ADS_GAIN08 (0b01000000)	// 0x40
 *          ADS_GAIN12 (0b01010000)	// 0x50
 *          ADS_GAIN24 (0b01100000)	// 0x60
 * @param `inputType` - [byte] - Selects the ADC channel input source, either:
 *          ADSINPUT_NORMAL     (0b00000000)
 *          ADSINPUT_SHORTED    (0b00000001)
 *          ADSINPUT_BIAS_MEAS  (0b00000010)
 *          ADSINPUT_MVDD       (0b00000011)
 *          ADSINPUT_TEMP       (0b00000100)
 *          ADSINPUT_TESTSIG    (0b00000101)
 *          ADSINPUT_BIAS_DRP   (0b00000110)
 *          ADSINPUT_BIAL_DRN   (0b00000111)
 * @param `bias` - [byte] (YES (1) -> Include in bias (default), NO (0) -> remove from bias)
 *          selects to include the channel input in bias generation
 * @param `srb2` - [byte] (YES (1) -> Connect this input to SRB2 (default),
 *                     NO (0) -> Disconnect this input from SRB2)
 *          Select to connect (YES) this channel's P input to the SRB2 pin. This closes
 *              a switch between P input and SRB2 for the given channel, and allows the
 *              P input to also remain connected to the ADC.
 * @param `srb1` - [byte] (YES (1) -> connect all N inputs to SRB1,
 *                     NO (0) -> Disconnect all N inputs from SRB1 (default))
 *          Select to connect (YES) all channels' N inputs to SRB1. This effects all pins,
 *              and disconnects all N inputs from the ADC.
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::channelSettingsSetForChannel(byte channelNumber, byte powerDown, byte gain, byte inputType, byte bias, byte srb2, byte srb1) {
    byte setting, targetSS;

    // contstrain the channel number to 0-15
    char index = getConstrainedChannelNumber(channelNumber);

    // Get the slave select pin for this channel
    byte targetSS = getTargetSSForChannelNumber(channelNumber);

    // first, disable any data collection
    SDATAC(targetSS); delay(1);      // exit Read Data Continuous mode to communicate with ADS

    setting = 0x00;

    // Set the power down bit
    if(powerDown == YES) {
        setting |= 0x80;
    }

    // Set the gain bits
    setting |= gain;

    // Set input type bits
    setting |= inputType;

    if(srb2 == YES){
        setting |= 0x08; // close this SRB2 switch
        useSRB2[index] = true;  // keep track of SRB2 usage
    }else{
        useSRB2[index] = false;
    }

    byte channelNumberRegister = 0x00;

    // Since we are addressing 8 bit registers, we need to subtract 8 from the
    //  channelNumber if we are addressing the Daisy ADS
    if (targetSS == DAISY_ADS) {
        channelNumberRegister = index - OPENBCI_NUMBER_OF_CHANNELS_DEFAULT;
    }
    WREG(CH1SET+channelNumberRegister, setting, targetSS);  // write this channel's register settings

    // add or remove from inclusion in BIAS generation
    setting = RREG(BIAS_SENSP,targetSS);       //get the current P bias settings
    if(bias == YES){
        useInBias[index] = true;
        bitSet(setting,channelNumberRegister);    //set this channel's bit to add it to the bias generation
    }else{
        useInBias[index] = false;
        bitClear(setting,channelNumberRegister);  // clear this channel's bit to remove from bias generation
    }
    WREG(BIAS_SENSP,setting,targetSS); delay(1); //send the modified byte back to the ADS

    setting = RREG(BIAS_SENSN,targetSS);       //get the current N bias settings
    if(bias == YES){
        bitSet(setting,channelNumberRegister);    //set this channel's bit to add it to the bias generation
    }else{
        bitClear(setting,channelNumberRegister);  // clear this channel's bit to remove from bias generation
    }
    WREG(BIAS_SENSN,setting,targetSS); delay(1); //send the modified byte back to the ADS

    // if SRB1 is closed or open for one channel, it will be the same for all channels
    if(srb1 == YES){
        for(int i=startChan; i<endChan; i++){
            channelSettings[i][SRB1_SET] = YES;
        }
        if(targetSS == BOARD_ADS) boardUseSRB1 = true;
        if(targetSS == DAISY_ADS) daisyUseSRB1 = true;
        setting = 0x20;     // close SRB1 swtich
    }
    if(srb1 == NO){
        for(int i=startChan; i<endChan; i++){
            channelSettings[i][SRB1_SET] = NO;
        }
        if(targetSS == BOARD_ADS) boardUseSRB1 = false;
        if(targetSS == DAISY_ADS) daisyUseSRB1 = false;
        setting = 0x00;     // open SRB1 switch
    }
    WREG(MISC1,setting,targetSS);
}

//  deactivate the given channel.
void OpenBCI_32bit_Class::deactivateChannel(byte N)
{
    byte setting, startChan, endChan, targetSS;
    if(N < 9){
        targetSS = BOARD_ADS; startChan = 0; endChan = 8;
    }else{
        if(!daisyPresent) { return; }
        targetSS = DAISY_ADS; startChan = 8; endChan = 16;
    }
    SDATAC(targetSS); delay(1);      // exit Read Data Continuous mode to communicate with ADS
    N = constrain(N-1,startChan,endChan-1);  //subtracts 1 so that we're counting from 0, not 1

    setting = RREG(CH1SET+(N-startChan),targetSS); delay(1); // get the current channel settings
    bitSet(setting,7);     // set bit7 to shut down channel
    bitClear(setting,3);   // clear bit3 to disclude from SRB2 if used
    WREG(CH1SET+(N-startChan),setting,targetSS); delay(1);     // write the new value to disable the channel

    //remove the channel from the bias generation...
    setting = RREG(BIAS_SENSP,targetSS); delay(1); //get the current bias settings
    bitClear(setting,N-startChan);                  //clear this channel's bit to remove from bias generation
    WREG(BIAS_SENSP,setting,targetSS); delay(1);   //send the modified byte back to the ADS

    setting = RREG(BIAS_SENSN,targetSS); delay(1); //get the current bias settings
    bitClear(setting,N-startChan);                  //clear this channel's bit to remove from bias generation
    WREG(BIAS_SENSN,setting,targetSS); delay(1);   //send the modified byte back to the ADS

    leadOffSettings[N][0] = leadOffSettings[N][1] = NO;
    changeChannelLeadOffDetect(N+1);
}

void OpenBCI_32bit_Class::activateChannel(byte N)
{
    byte setting, startChan, endChan, targetSS;
    if(N < 9){
        targetSS = BOARD_ADS; startChan = 0; endChan = 8;
    }else{
        if(!daisyPresent) { return; }
        targetSS = DAISY_ADS; startChan = 8; endChan = 16;
    }

    N = constrain(N-1,startChan,endChan-1);  // 0-7 or 8-15

    SDATAC(targetSS);  // exit Read Data Continuous mode to communicate with ADS
    setting = 0x00;
    //  channelSettings[N][POWER_DOWN] = NO; // keep track of channel on/off in this array  REMOVE?
    setting |= channelSettings[N][GAIN_SET]; // gain
    setting |= channelSettings[N][INPUT_TYPE_SET]; // input code
    if(useSRB2[N] == true){channelSettings[N][SRB2_SET] = YES;}else{channelSettings[N][SRB2_SET] = NO;}
    if(channelSettings[N][SRB2_SET] == YES) {bitSet(setting,3);} // close this SRB2 switch
    WREG(CH1SET+(N-startChan),setting,targetSS);
    // add or remove from inclusion in BIAS generation
    if(useInBias[N]){channelSettings[N][BIAS_SET] = YES;}else{channelSettings[N][BIAS_SET] = NO;}
    setting = RREG(BIAS_SENSP,targetSS);       //get the current P bias settings
    if(channelSettings[N][BIAS_SET] == YES){
        bitSet(setting,N-startChan);    //set this channel's bit to add it to the bias generation
        useInBias[N] = true;
    }else{
        bitClear(setting,N-startChan);  // clear this channel's bit to remove from bias generation
        useInBias[N] = false;
    }
    WREG(BIAS_SENSP,setting,targetSS); delay(1); //send the modified byte back to the ADS
    setting = RREG(BIAS_SENSN,targetSS);       //get the current N bias settings
    if(channelSettings[N][BIAS_SET] == YES){
        bitSet(setting,N-startChan);    //set this channel's bit to add it to the bias generation
    }else{
        bitClear(setting,N-startChan);  // clear this channel's bit to remove from bias generation
    }
    WREG(BIAS_SENSN,setting,targetSS); delay(1); //send the modified byte back to the ADS

    setting = 0x00;
    if(targetSS == BOARD_ADS && boardUseSRB1 == true) setting = 0x20;
    if(targetSS == DAISY_ADS && daisyUseSRB1 == true) setting = 0x20;
    WREG(MISC1,setting,targetSS);     // close all SRB1 swtiches
}

//////////////////////////////////////////////
///////////// LEAD OFF METHODS ///////////////
//////////////////////////////////////////////

/**
 * @description Runs through the `leadOffSettings` global array to set/change
 *                  the lead off signals for all inputs of all channels.
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::leadOffSetForAllChannels(void) {
    byte channelNumberUpperLimit;

    // The upper limit of the channels, either 8 or 16
    channelNumberUpperLimit = daisyPresent ? OPENBCI_NUMBER_OF_CHANNELS_DAISY : OPENBCI_NUMBER_OF_CHANNELS_DEFAULT;

    // Loop through all channels
    for (int i = 1; i <= channelNumberUpperLimit; i++) {
        leadOffSetForChannel((byte)i,leadOffSettings[i-1][PCHAN],leadOffSettings[i-1][NCHAN]);
    }
}

/**
 * @description Used to set lead off for a channel
 * @param `channelNumber` - [byte] - The channel you want to change
 * @param `pInput` - [byte] - Apply signal to P input, either ON (1) or OFF (0)
 * @param `nInput` - [byte] - Apply signal to N input, either ON (1) or OFF (0)
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::leadOffSetForChannel(byte channelNumber, byte pInput, byte nInput) {

    // contstrain the channel number to 0-15
    channelNumber = getConstrainedChannelNumber(channelNumber);

    // Get the slave select pin for this channel
    byte targetSS = getTargetSSForChannelNumber(channelNumber);

    // exit Read Data Continuous mode to communicate with ADS
    SDATAC(targetSS);
    delay(1);

    // Read P register
    byte P_setting = RREG(LOFF_SENSP,targetSS);

    // Read N register
    byte N_setting = RREG(LOFF_SENSN,targetSS);

    // Since we are addressing 8 bit registers, we need to subtract 8 from the
    //  channelNumber if we are addressing the Daisy ADS
    if (targetSS == DAISY_ADS) {
        channelNumber -= OPENBCI_NUMBER_OF_CHANNELS_DEFAULT;
    }

    // If pInput is ON then we want to set, otherwise we want to clear
    if (pInput == ON) {
        bitSet(P_setting, channelNumber);
    } else {
        bitClear(P_setting, channelNumber);
    }
    // Write to the P register
    WREG(LOFF_SENSP,P_setting,targetSS);

    // If nInput is ON then we want to set, otherwise we want to clear
    if (nInput == ON) {
        bitSet(N_setting, channelNumber);
    } else {
        bitClear(N_setting, channelNumber);
    }
    // Write to the N register
    WREG(LOFF_SENSN,N_setting,targetSS);
}

/**
 * @description Convert user channelNumber for use in array indexs by subtracting 1,
 *                  also make sure N is not greater than 15 or less than 0
 * @param `channelNumber` - [byte] - The channel number
 * @return [byte] - Constrained channel number
 */
char OpenBCI_32bit_Class::getConstrainedChannelNumber(byte channelNumber) {
    return constrain(channelNumber - 1, 0, OPENBCI_NUMBER_OF_CHANNELS_DAISY - 1);
}

/**
 * @description Get slave select pin for channelNumber
 * @param `channelNumber` - [byte] - The channel number
 * @return [byte] - Constrained channel number
 */
char OpenBCI_32bit_Class::getTargetSSForChannelNumber(byte channelNumber) {
    // Is channelNumber in the range of default [0,7]
    if (channelNumber < OPENBCI_NUMBER_OF_CHANNELS_DEFAULT) {
        return BOARD_ADS;
    } else {
        return DAISY_ADS;
    }
}

/**
 * @description This sets the LOFF register on the Board ADS and the Daisy ADS
 * @param `amplitudeCode` - [byte] - The amplitude of the of impedance signal.
 *                 See `.setleadOffForSS()` for complete description
 * @param `freqCode` - [byte] - The frequency of the impedance signal can be either.
 *                 See `.setleadOffForSS()` for complete description
 * @author AJ Keller (@pushtheworldllc)
 */
void OpenBCI_32bit_Class::leadOffConfigureSignalForAll(byte amplitudeCode, byte freqCode)
{
    // Set the lead off detection for the on board ADS
    leadOffConfigureSignalForTargetSS(BOARD_ADS, amplitudeCode, freqCode);

    // if the daisy board is present, set that register as well
    if (daisyPresent) {
        leadOffConfigureSignalForTargetSS(DAISY_ADS, amplitudeCode, freqCode);
    }
}

/**
 * @description This sets the LOFF (lead off) register for the given ADS with slave
 *                  select
 * @param `targetSS` - [byte] - The Slave Select pin.
 * @param `amplitudeCode` - [byte] - The amplitude of the of impedance signal.
 *          LOFF_MAG_6NA        (0b00000000)
 *          LOFF_MAG_24NA       (0b00000100)
 *          LOFF_MAG_6UA        (0b00001000)
 *          LOFF_MAG_24UA       (0b00001100)
 * @param `freqCode` - [byte] - The frequency of the impedance signal can be either.
 *          LOFF_FREQ_DC        (0b00000000)
 *          LOFF_FREQ_7p8HZ     (0b00000001)
 *          LOFF_FREQ_31p2HZ    (0b00000010)
 *          LOFF_FREQ_FS_4      (0b00000011)
 * @author Joel/Leif/Conor (@OpenBCI) Summer 2014
 */
void OpenBCI_32bit_Class::leadOffConfigureSignalForTargetSS(byte targetSS, byte amplitudeCode, byte freqCode) {
    byte setting;

    amplitudeCode &= 0b00001100;  //only these two bits should be used
    freqCode &= 0b00000011;  //only these two bits should be used

    setting = RREG(LOFF,targetSS); //get the current bias settings
    //reconfigure the byte to get what we want
    setting &= 0b11110000;  //clear out the last four bits
    setting |= amplitudeCode;  //set the amplitude
    setting |= freqCode;    //set the frequency
    //send the config byte back to the hardware
    WREG(LOFF,setting,targetSS); delay(1);  //send the modified byte back to the ADS
}

//Configure the test signals that can be inernally generated by the ADS1299
void OpenBCI_32bit_Class::configureInternalTestSignal(byte amplitudeCode, byte freqCode)
{
    byte setting, targetSS;
    for(int i=0; i<2; i++){
        if(i == 0){ targetSS = BOARD_ADS;}
        if(i == 1){
            if(daisyPresent == false){ return; }
            targetSS = DAISY_ADS;
        }
        if (amplitudeCode == ADSTESTSIG_NOCHANGE) amplitudeCode = (RREG(CONFIG2,targetSS) & (0b00000100));
        if (freqCode == ADSTESTSIG_NOCHANGE) freqCode = (RREG(CONFIG2,targetSS) & (0b00000011));
        freqCode &= 0b00000011;  		//only the last two bits are used
        amplitudeCode &= 0b00000100;  	//only this bit is used
        byte setting = 0b11010000 | freqCode | amplitudeCode;  //compose the code
        WREG(CONFIG2,setting,targetSS); delay(1);
    }
}

void OpenBCI_32bit_Class::changeInputType(byte inputCode){

    for(int i=0; i<numChannels; i++){
        channelSettings[i][INPUT_TYPE_SET] = inputCode;
    }

    channelSettingsArraySetForAll();
}

// Start continuous data acquisition
void OpenBCI_32bit_Class::startADS(void) // NEEDS ADS ADDRESS, OR BOTH?
{
    sampleCounter = 0;
    firstDataPacket = true;
    RDATAC(BOTH_ADS); // enter Read Data Continuous mode
    delay(1);
    START(BOTH_ADS);  // start the data acquisition
    delay(1);
    isRunning = true;
}

// Query to see if data is available from the ADS1299...return TRUE is data is available
boolean OpenBCI_32bit_Class::isDataAvailable(void)
{
    return (!(digitalRead(ADS_DRDY)));
}

// CALLED WHEN DRDY PIN IS ASSERTED. NEW ADS DATA AVAILABLE!
void OpenBCI_32bit_Class::updateChannelData(){
    updateBoardData();
    if(daisyPresent) {updateDaisyData();}
}

void OpenBCI_32bit_Class::updateBoardData(){
    byte inByte;
    int byteCounter = 0;

    if(daisyPresent && !firstDataPacket){
        for(int i=0; i<8; i++){  // shift and average the byte arrays
            lastBoardChannelDataInt[i] = boardChannelDataInt[i]; // remember the last samples
        }
    }
    csLow(BOARD_ADS);       //  open SPI
    for(int i=0; i<3; i++){
        inByte = xfer(0x00);    //  read status register (1100 + LOFF_STATP + LOFF_STATN + GPIO[7:4])
        boardStat = (boardStat << 8) | inByte;
    }
    for(int i = 0; i<8; i++){
        for(int j=0; j<3; j++){   //  read 24 bits of channel data in 8 3 byte chunks
            inByte = xfer(0x00);
            boardChannelDataRaw[byteCounter] = inByte;  // raw data goes here
            byteCounter++;
            boardChannelDataInt[i] = (boardChannelDataInt[i]<<8) | inByte;  // int data goes here
        }
    }
    csHigh(BOARD_ADS);        //  close SPI
    // need to convert 24bit to 32bit if using the filter
    for(int i=0; i<8; i++){     // convert 3 byte 2's compliment to 4 byte 2's compliment
    if(bitRead(boardChannelDataInt[i],23) == 1){
        boardChannelDataInt[i] |= 0xFF000000;
    }else{
        boardChannelDataInt[i] &= 0x00FFFFFF;
    }
}
if(daisyPresent && !firstDataPacket){
    byteCounter = 0;
    for(int i=0; i<8; i++){   // take the average of this and the last sample
        meanBoardChannelDataInt[i] = (lastBoardChannelDataInt[i] + boardChannelDataInt[i])/2;
    }
    for(int i=0; i<8; i++){  // place the average values in the meanRaw array
        for(int b=2; b>=0; b--){
            meanBoardDataRaw[byteCounter] = (meanBoardChannelDataInt[i] >> (b*8)) & 0xFF;
            byteCounter++;
        }
    }
}

if(firstDataPacket == true){firstDataPacket = false;}
}

void OpenBCI_32bit_Class::updateDaisyData(){
    byte inByte;
    int byteCounter = 0;

    if(daisyPresent && !firstDataPacket){
        for(int i=0; i<8; i++){  // shift and average the byte arrays
            lastDaisyChannelDataInt[i] = daisyChannelDataInt[i]; // remember the last samples
        }
    }

    csLow(DAISY_ADS);       //  open SPI
    for(int i=0; i<3; i++){
        inByte = xfer(0x00);    //  read status register (1100 + LOFF_STATP + LOFF_STATN + GPIO[7:4])
        daisyStat = (daisyStat << 8) | inByte;
    }
    for(int i = 0; i<8; i++){
        for(int j=0; j<3; j++){   //  read 24 bits of channel data in 8 3 byte chunks
            inByte = xfer(0x00);
            daisyChannelDataRaw[byteCounter] = inByte;  // raw data goes here
            byteCounter++;
            daisyChannelDataInt[i] = (daisyChannelDataInt[i]<<8) | inByte; // int data goes here
        }
    }
    csHigh(DAISY_ADS);        //  close SPI
    // need to convert 24bit to 32bit
    for(int i=0; i<8; i++){     // convert 3 byte 2's compliment to 4 byte 2's compliment
    if(bitRead(daisyChannelDataInt[i],23) == 1){
        daisyChannelDataInt[i] |= 0xFF000000;
    }else{
        daisyChannelDataInt[i] &= 0x00FFFFFF;
    }
}
if(daisyPresent && !firstDataPacket){
    byteCounter = 0;
    for(int i=0; i<8; i++){   // average this sample with the last sample
        meanDaisyChannelDataInt[i] = (lastDaisyChannelDataInt[i] + daisyChannelDataInt[i])/2;
    }
    for(int i=0; i<8; i++){  // place the average values in the meanRaw array
        for(int b=2; b>=0; b--){
            meanDaisyDataRaw[byteCounter] = (meanDaisyChannelDataInt[i] >> (b*8)) & 0xFF;
            byteCounter++;
        }
    }
}

if(firstDataPacket == true){firstDataPacket = false;}
}

// Stop the continuous data acquisition
void OpenBCI_32bit_Class::stopADS()
{
    STOP(BOTH_ADS);     // stop the data acquisition
    delay(1);
    SDATAC(BOTH_ADS);   // stop Read Data Continuous mode to communicate with ADS
    delay(1);
    isRunning = false;
}


//write as binary each channel's data
void OpenBCI_32bit_Class::ADS_writeChannelData()
{

    if(daisyPresent){
        if(sampleCounter % 2 != 0){ //CHECK SAMPLE ODD-EVEN AND SEND THE APPROPRIATE ADS DATA
            for (int i=0; i<24; i++){
                Serial0.write(meanBoardDataRaw[i]); // send board data on odd samples
            }
        }else{
            for (int i=0; i<24; i++){
                Serial0.write(meanDaisyDataRaw[i]); // send daisy data on even samples
            }
        }
    }else{
        for(int i=0; i<24; i++){
            Serial0.write(boardChannelDataRaw[i]);
        }
    }
}


//print out the state of all the control registers
void OpenBCI_32bit_Class::printADSregisters(int targetSS)
{
    boolean prevverbosityState = verbosity;
    verbosity = true;						// set up for verbosity output
    RREGS(0x00,0x0C,targetSS);     	// read out the first registers
    delay(10);  						// stall to let all that data get read by the PC
    RREGS(0x0D,0x17-0x0D,targetSS);	// read out the rest
    verbosity = prevverbosityState;
}

byte OpenBCI_32bit_Class::ADS_getDeviceID(int targetSS) {      // simple hello world com check
    byte data = RREG(ID_REG,targetSS);
    if(verbosity){            // verbosity otuput
        Serial0.print("On Board ADS ID ");
        printHex(data); Serial0.println();
    }
    return data;
}

//System Commands
void OpenBCI_32bit_Class::WAKEUP(int targetSS) {
    csLow(targetSS);
    xfer(_WAKEUP);
    csHigh(targetSS);
    delayMicroseconds(3);     //must wait 4 tCLK cycles before sending another command (Datasheet, pg. 35)
}

void OpenBCI_32bit_Class::STANDBY(int targetSS) {    // only allowed to send WAKEUP after sending STANDBY
    csLow(targetSS);
    xfer(_STANDBY);
    csHigh(targetSS);
}

void OpenBCI_32bit_Class::RESET(int targetSS) {      // reset all the registers to default settings
    csLow(targetSS);
    xfer(_RESET);
    delayMicroseconds(12);    //must wait 18 tCLK cycles to execute this command (Datasheet, pg. 35)
    csHigh(targetSS);
}

void OpenBCI_32bit_Class::START(int targetSS) {      //start data conversion
    csLow(targetSS);
    xfer(_START);           // KEEP ON-BOARD AND ON-DAISY IN SYNC
    csHigh(targetSS);
}

void OpenBCI_32bit_Class::STOP(int targetSS) {     //stop data conversion
    csLow(targetSS);
    xfer(_STOP);            // KEEP ON-BOARD AND ON-DAISY IN SYNC
    csHigh(targetSS);
}

void OpenBCI_32bit_Class::RDATAC(int targetSS) {
    csLow(targetSS);
    xfer(_RDATAC);      // read data continuous
    csHigh(targetSS);
    delayMicroseconds(3);
}
void OpenBCI_32bit_Class::SDATAC(int targetSS) {
    csLow(targetSS);
    xfer(_SDATAC);
    csHigh(targetSS);
    delayMicroseconds(10);   //must wait at least 4 tCLK cycles after executing this command (Datasheet, pg. 37)
}


//  THIS NEEDS CLEANING AND UPDATING TO THE NEW FORMAT
void OpenBCI_32bit_Class::RDATA(int targetSS) {          //  use in Stop Read Continuous mode when DRDY goes low
    byte inByte;            //  to read in one sample of the channels
    csLow(targetSS);        //  open SPI
    xfer(_RDATA);         //  send the RDATA command
    for(int i=0; i<3; i++){   //  read in the status register and new channel data
        inByte = xfer(0x00);
        boardStat = (boardStat<<8) | inByte; //  read status register (1100 + LOFF_STATP + LOFF_STATN + GPIO[7:4])
    }
    if(targetSS == BOARD_ADS){
        for(int i = 0; i<8; i++){
            for(int j=0; j<3; j++){   //  read in the new channel data
                inByte = xfer(0x00);
                boardChannelDataInt[i] = (boardChannelDataInt[i]<<8) | inByte;
            }
        }
        for(int i=0; i<8; i++){
            if(bitRead(boardChannelDataInt[i],23) == 1){  // convert 3 byte 2's compliment to 4 byte 2's compliment
            boardChannelDataInt[i] |= 0xFF000000;
        }else{
            boardChannelDataInt[i] &= 0x00FFFFFF;
        }
    }
}else{
    for(int i = 0; i<8; i++){
        for(int j=0; j<3; j++){   //  read in the new channel data
            inByte = xfer(0x00);
            daisyChannelDataInt[i] = (daisyChannelDataInt[i]<<8) | inByte;
        }
    }
    for(int i=0; i<8; i++){
        if(bitRead(daisyChannelDataInt[i],23) == 1){  // convert 3 byte 2's compliment to 4 byte 2's compliment
        daisyChannelDataInt[i] |= 0xFF000000;
    }else{
        daisyChannelDataInt[i] &= 0x00FFFFFF;
    }
}
}
csHigh(targetSS);        //  close SPI


}

byte OpenBCI_32bit_Class::RREG(byte _address,int targetSS) {    //  reads ONE register at _address
    byte opcode1 = _address + 0x20;   //  RREG expects 001rrrrr where rrrrr = _address
    csLow(targetSS);        //  open SPI
    xfer(opcode1);          //  opcode1
    xfer(0x00);           //  opcode2
    regData[_address] = xfer(0x00);//  update mirror location with returned byte
    csHigh(targetSS);       //  close SPI
    if (verbosity){           //  verbosity output
        printRegisterName(_address);
        printHex(_address);
        Serial0.print(", ");
        printHex(regData[_address]);
        Serial0.print(", ");
        for(byte j = 0; j<8; j++){
            Serial0.print(bitRead(regData[_address], 7-j));
            if(j!=7) Serial0.print(", ");
        }

        Serial0.println();
    }
    return regData[_address];     // return requested register value
}


// Read more than one register starting at _address
void OpenBCI_32bit_Class::RREGS(byte _address, byte _numRegistersMinusOne, int targetSS) {

    byte opcode1 = _address + 0x20;   //  RREG expects 001rrrrr where rrrrr = _address
    csLow(targetSS);        //  open SPI
    xfer(opcode1);          //  opcode1
    xfer(_numRegistersMinusOne);  //  opcode2
    for(int i = 0; i <= _numRegistersMinusOne; i++){
        regData[_address + i] = xfer(0x00);   //  add register byte to mirror array
    }
    csHigh(targetSS);       //  close SPI
    if(verbosity){            //  verbosity output
        for(int i = 0; i<= _numRegistersMinusOne; i++){
            printRegisterName(_address + i);
            printHex(_address + i);
            Serial0.print(", ");
            printHex(regData[_address + i]);
            Serial0.print(", ");
            for(int j = 0; j<8; j++){
                Serial0.print(bitRead(regData[_address + i], 7-j));
                if(j!=7) Serial0.print(", ");
            }
            Serial0.println();
            delay(30);
        }
    }
}

void OpenBCI_32bit_Class::WREG(byte _address, byte _value, int target_SS) { //  Write ONE register at _address
    byte opcode1 = _address + 0x40;   //  WREG expects 010rrrrr where rrrrr = _address
    csLow(target_SS);        //  open SPI
    xfer(opcode1);          //  Send WREG command & address
    xfer(0x00);           //  Send number of registers to read -1
    xfer(_value);         //  Write the value to the register
    csHigh(target_SS);       //  close SPI
    regData[_address] = _value;     //  update the mirror array
    if(verbosity){            //  verbosity output
        Serial0.print("Register ");
        printHex(_address);
        Serial0.println(" modified.");
    }
}

void OpenBCI_32bit_Class::WREGS(byte _address, byte _numRegistersMinusOne, int targetSS) {
    byte opcode1 = _address + 0x40;   //  WREG expects 010rrrrr where rrrrr = _address
    csLow(targetSS);        //  open SPI
    xfer(opcode1);          //  Send WREG command & address
    xfer(_numRegistersMinusOne);  //  Send number of registers to read -1
    for (int i=_address; i <=(_address + _numRegistersMinusOne); i++){
        xfer(regData[i]);     //  Write to the registers
    }
    csHigh(targetSS);
    if(verbosity){
        Serial0.print("Registers ");
        printHex(_address); Serial0.print(" to ");
        printHex(_address + _numRegistersMinusOne);
        Serial0.println(" modified");
    }
}


// <<<<<<<<<<<<<<<<<<<<<<<<<  END OF ADS1299 FUNCTIONS  >>>>>>>>>>>>>>>>>>>>>>>>>
// ******************************************************************************
// <<<<<<<<<<<<<<<<<<<<<<<<<  LIS3DH FUNCTIONS  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


void OpenBCI_32bit_Class::initialize_accel(byte g){
    byte setting =  g | 0x08;           // mask the g range for REG4
    pinMode(LIS3DH_DRDY,INPUT);   // setup dataReady interupt from accelerometer
    LIS3DH_write(TMP_CFG_REG, 0x00);  // DISable ADC inputs, enable temperature sensor
    LIS3DH_write(CTRL_REG1, 0x08);    // disable accel, low power mode
    LIS3DH_write(CTRL_REG2, 0x00);    // don't use the high pass filter
    LIS3DH_write(CTRL_REG3, 0x00);    // no interrupts yet
    LIS3DH_write(CTRL_REG4, setting); // set scale to g, high resolution
    LIS3DH_write(CTRL_REG5, 0x00);    // no boot, no fifo
    LIS3DH_write(CTRL_REG6, 0x00);
    LIS3DH_write(REFERENCE, 0x00);
    DRDYpinValue = lastDRDYpinValue = digitalRead(LIS3DH_DRDY);  // take a reading to seed these variables
}

void OpenBCI_32bit_Class::enable_accel(byte Hz){
    for(int i=0; i<3; i++){
        axisData[i] = 0;            // clear the axisData array so we don't get any stale news
    }
    byte setting = Hz | 0x07;           // mask the desired frequency
    LIS3DH_write(CTRL_REG1, setting);   // set freq and enable all axis in normal mode
    LIS3DH_write(CTRL_REG3, 0x10);      // enable DRDY1 on INT1 (tied to PIC pin 0, LIS3DH_DRDY)
}

void OpenBCI_32bit_Class::disable_accel(){
    LIS3DH_write(CTRL_REG1, 0x08);      // power down, low power mode
    LIS3DH_write(CTRL_REG3, 0x00);      // disable DRDY1 on INT1
}

byte OpenBCI_32bit_Class::LIS3DH_getDeviceID(){
    return LIS3DH_read(WHO_AM_I);
}

boolean OpenBCI_32bit_Class::LIS3DH_DataAvailable(){
    boolean x = false;
    if((LIS3DH_read(STATUS_REG2) & 0x08) > 0) x = true;  // read STATUS_REG
    return x;
}

boolean OpenBCI_32bit_Class::LIS3DH_DataReady(){
    boolean r = false;
    DRDYpinValue = digitalRead(LIS3DH_DRDY);  // take a look at LIS3DH_DRDY pin
    if(DRDYpinValue != lastDRDYpinValue){     // if the value has changed since last looking
        if(DRDYpinValue == HIGH){               // see if this is the rising edge
            r = true;                             // if so, there is fresh data!
        }
        lastDRDYpinValue = DRDYpinValue;        // keep track of the changing pin
    }
    return r;
}

void OpenBCI_32bit_Class::LIS3DH_writeAxisData(void){
    for(int i=0; i<3; i++){
        Serial0.write(highByte(axisData[i])); // write 16 bit axis data MSB first
        Serial0.write(lowByte(axisData[i]));  // axisData is array of type short (16bit)
        axisData[i] = 0;
    }
}

byte OpenBCI_32bit_Class::LIS3DH_read(byte reg){
    reg |= READ_REG;                    // add the READ_REG bit
    csLow(LIS3DH_SS);                   // take spi
    spi.transfer(reg);                  // send reg to read
    byte inByte = spi.transfer(0x00);   // retrieve data
    csHigh(LIS3DH_SS);                  // release spi
    return inByte;
}

void OpenBCI_32bit_Class::LIS3DH_write(byte reg, byte value){
    csLow(LIS3DH_SS);         // take spi
    spi.transfer(reg);        // send reg to write
    spi.transfer(value);      // write value
    csHigh(LIS3DH_SS);        // release spi
}

int OpenBCI_32bit_Class::LIS3DH_read16(byte reg){    // use for reading axis data.
    int inData;
    reg |= READ_REG | READ_MULTI;   // add the READ_REG and READ_MULTI bits
    csLow(LIS3DH_SS);               // take spi
    spi.transfer(reg);              // send reg to start reading from
    inData = spi.transfer(0x00) | (spi.transfer(0x00) << 8);  // get the data and arrange it
    csHigh(LIS3DH_SS);              // release spi
    return inData;
}

int OpenBCI_32bit_Class::getX(){
    return LIS3DH_read16(OUT_X_L);
}

int OpenBCI_32bit_Class::getY(){
    return LIS3DH_read16(OUT_Y_L);
}

int OpenBCI_32bit_Class::getZ(){
    return LIS3DH_read16(OUT_Z_L);
}

void OpenBCI_32bit_Class::LIS3DH_updateAxisData(){
    axisData[0] = getX();
    axisData[1] = getY();
    axisData[2] = getZ();
}

void OpenBCI_32bit_Class::LIS3DH_readAllRegs(){

    byte inByte;

    for (int i = STATUS_REG_AUX; i <= WHO_AM_I; i++){
        inByte = LIS3DH_read(i);
        Serial0.print("0x0");Serial0.print(i,HEX);
        Serial0.print("\t");Serial0.println(inByte,HEX);
        delay(20);
    }
    Serial0.println();

    for (int i = TMP_CFG_REG; i <= INT1_DURATION; i++){
        inByte = LIS3DH_read(i);
        // printRegisterName(i);
        Serial0.print("0x");Serial0.print(i,HEX);
        Serial0.print("\t");Serial0.println(inByte,HEX);
        delay(20);
    }
    Serial0.println();

    for (int i = CLICK_CFG; i <= TIME_WINDOW; i++){
        inByte = LIS3DH_read(i);
        Serial0.print("0x");Serial0.print(i,HEX);
        Serial0.print("\t");Serial0.println(inByte,HEX);
        delay(20);
    }

}



// <<<<<<<<<<<<<<<<<<<<<<<<<  END OF LIS3DH FUNCTIONS >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



// String-Byte converters for ADS
void OpenBCI_32bit_Class::printRegisterName(byte _address) {
    switch(_address){
        case ID_REG:
        Serial0.print("ADS_ID, "); break;
        case CONFIG1:
        Serial0.print("CONFIG1, "); break;
        case CONFIG2:
        Serial0.print("CONFIG2, "); break;
        case CONFIG3:
        Serial0.print("CONFIG3, "); break;
        case LOFF:
        Serial0.print("LOFF, "); break;
        case CH1SET:
        Serial0.print("CH1SET, "); break;
        case CH2SET:
        Serial0.print("CH2SET, "); break;
        case CH3SET:
        Serial0.print("CH3SET, "); break;
        case CH4SET:
        Serial0.print("CH4SET, "); break;
        case CH5SET:
        Serial0.print("CH5SET, "); break;
        case CH6SET:
        Serial0.print("CH6SET, "); break;
        case CH7SET:
        Serial0.print("CH7SET, "); break;
        case CH8SET:
        Serial0.print("CH8SET, "); break;
        case BIAS_SENSP:
        Serial0.print("BIAS_SENSP, "); break;
        case BIAS_SENSN:
        Serial0.print("BIAS_SENSN, "); break;
        case LOFF_SENSP:
        Serial0.print("LOFF_SENSP, "); break;
        case LOFF_SENSN:
        Serial0.print("LOFF_SENSN, "); break;
        case LOFF_FLIP:
        Serial0.print("LOFF_FLIP, "); break;
        case LOFF_STATP:
        Serial0.print("LOFF_STATP, "); break;
        case LOFF_STATN:
        Serial0.print("LOFF_STATN, "); break;
        case GPIO:
        Serial0.print("GPIO, "); break;
        case MISC1:
        Serial0.print("MISC1, "); break;
        case MISC2:
        Serial0.print("MISC2, "); break;
        case CONFIG4:
        Serial0.print("CONFIG4, "); break;
        default:
        break;
    }
}

// Used for printing HEX in verbosity feedback mode
void OpenBCI_32bit_Class::printHex(byte _data){
    Serial0.print("0x");
    if(_data < 0x10) Serial0.print("0");
    Serial0.print(_data, HEX);
}

/**
 * @description Converts ascii character to byte value for channel setting bytes
 * @param `asciiChar` - [char] - The ascii character to convert
 * @return [char] - Byte number value of acsii character, defaults to 0
 * @author AJ Keller (@pushtheworldllc)
 */
char OpenBCI_32bit_Class::getChannelCommandForAsciiChar(char asciiChar) {
    switch(asciiChar){
        case OPENBCI_CHANNEL_CMD_CHANNEL_1:
            return 0x00;
        case OPENBCI_CHANNEL_CMD_CHANNEL_2:
            return 0x01;
        case OPENBCI_CHANNEL_CMD_CHANNEL_3:
            return 0x02;
        case OPENBCI_CHANNEL_CMD_CHANNEL_4:
            return 0x03;
        case OPENBCI_CHANNEL_CMD_CHANNEL_5:
            return 0x04;
        case OPENBCI_CHANNEL_CMD_CHANNEL_6:
            return 0x05;
        case OPENBCI_CHANNEL_CMD_CHANNEL_7:
            return 0x06;
        case OPENBCI_CHANNEL_CMD_CHANNEL_8:
            return 0x07;
        case OPENBCI_CHANNEL_CMD_CHANNEL_9:
            return 0x08;
        case OPENBCI_CHANNEL_CMD_CHANNEL_10:
            return 0x09;
        case OPENBCI_CHANNEL_CMD_CHANNEL_11:
            return 0x0A;
        case OPENBCI_CHANNEL_CMD_CHANNEL_12:
            return 0x0B;
        case OPENBCI_CHANNEL_CMD_CHANNEL_13:
            return 0x0C;
        case OPENBCI_CHANNEL_CMD_CHANNEL_14:
            return 0x0D;
        case OPENBCI_CHANNEL_CMD_CHANNEL_15:
            return 0x0E;
        case OPENBCI_CHANNEL_CMD_CHANNEL_16:
            return 0x0F;
        default:
            return 0x00;
    }
}

/**
 * @description Converts ascii '0' to number 0 and ascii '1' to number 1
 * @param `asciiChar` - [char] - The ascii character to convert
 * @return [char] - Byte number value of acsii character, defaults to 0
 * @author AJ Keller (@pushtheworldllc)
 */
char OpenBCI_32bit_Class::getYesOrNoForAsciiChar(char asciiChar) {
    switch (asciiChar) {
        case '1':
            return ACTIVATE;
        case '0':
        default:
            return DEACTIVATE;
    }
}

/**
 * @description Converts ascii character to get gain from channel settings
 * @param `asciiChar` - [char] - The ascii character to convert
 * @return [char] - Byte number value of acsii character, defaults to 0
 * @author AJ Keller (@pushtheworldllc)
 */
char OpenBCI_32bit_Class::getGainForAsciiChar(char asciiChar) {

    char output = 0x00;

    if (asciiChar < '0' && asciiChar > '6') {
        asciiChar = '6'; // Default to 24
    }

    output = asciiChar - '0';

    return output << 4;
}

/**
 * @description Converts ascii character to get gain from channel settings
 * @param `asciiChar` - [char] - The ascii character to convert
 * @return [char] - Byte number value of acsii character, defaults to 0
 * @author AJ Keller (@pushtheworldllc)
 */
char OpenBCI_32bit_Class::getNumberForAsciiChar(char asciiChar) {
    if (asciiChar < '0' && asciiChar > '9') {
        asciiChar = '0';
    }

    // Convert ascii char to number
    asciiChar -= '0';

    return asciiChar;
}
