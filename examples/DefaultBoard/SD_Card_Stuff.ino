#define BLOCK_5MIN    16890 
#define BLOCK_15MIN  (BLOCK_5MIN*3)    
#define BLOCK_30MIN  (BLOCK_15MIN*2)   
#define BLOCK_1HR    (BLOCK_30MIN*2)  
#define BLOCK_2HR    (BLOCK_1HR*2)    
#define BLOCK_4HR    (BLOCK_1HR*4)    
#define BLOCK_12HR   (BLOCK_1HR*12)  
#define BLOCK_24HR   (BLOCK_1HR*24) 

#define OVER_DIM      20 // make room for up to 20 write-time overruns
#define ERROR_LED     false
#define OK_LED        true

char    fileSize = '0';  // SD file size indicator
int blockCounter =  0 ;


uint32_t BLOCK_COUNT;
SdFile openfile;  // want to put this before setup...
Sd2Card card(&board.spi,SD_SS);// SPI needs to be init'd before here
SdVolume volume;
SdFile root;
uint8_t* pCache;      // array that points to the block buffer on SD card
uint32_t MICROS_PER_BLOCK = 2000; // block write longer than this will get flaged
uint32_t bgnBlock, endBlock; // file extent bookends
int byteCounter = 0;    // used to hold position in cache
//int blockCounter;       // count up to BLOCK_COUNT with this
boolean openvol;
boolean cardInit = false;
boolean fileIsOpen = false;
uint8_t BLOCK_DIV = 1; // DEFAULT VALUE

struct {
  uint32_t block;   // holds block number that over-ran
  uint32_t micro;  // holds the length of this of over-run
} over[OVER_DIM];

uint32_t overruns;      // count the number of overruns
uint32_t maxWriteTime;  // keep track of longest write time
uint32_t minWriteTime;  // and shortest write time
uint32_t t;        // used to measure total file write time
uint8_t ERROR_BLINKS = 3;
uint8_t OK_BLINKS    = 3;


byte fileTens, fileOnes;  // enumerate succesive files on card and store number in EEPROM
char currentFileName[] = "OBCI_00.TXT"; // file name will enumerate in hex 00 - FF
prog_char samplingFreq[] PROGMEM = {"\n%SamplingFreq:\n"};  // 16
prog_char elapsedTime[] PROGMEM = {"%Total time mS:\n"};  // 17
prog_char minTime[] PROGMEM = {  "%min Write time uS:\n"};  // 20
prog_char maxTime[] PROGMEM = {  "%max Write time uS:\n"};  // 20
prog_char overNum[] PROGMEM = {  "%Over:\n"};               //  7
prog_char blockTime[] PROGMEM = {  "%block, uS\n"};         // 11    74 chars + 2 32(16) + 2 16(8) = 98 + (n 32x2) up to 24 overruns...
prog_char stopStamp[] PROGMEM = {  "%STOP AT\n"};      // used to stamp SD record when stopped by PC
prog_char startStamp[] PROGMEM = {  "%START AT\n"};    // used to stamp SD record when started by PC



bool LED_SD_Status_Indication(uint8_t blinks_num, uint8_t blink_period_num, bool ok_indication){
  
  for(uint8_t i=0; i<blinks_num; i++){
     digitalWrite(OPENBCI_PIN_LED, LOW);
     delay(blink_period_num);
     digitalWrite(OPENBCI_PIN_LED, HIGH);
     delay(blink_period_num);
  }
  
  if(ok_indication){
    digitalWrite(OPENBCI_PIN_LED,HIGH);
    return true;
  }else {
    digitalWrite(OPENBCI_PIN_LED,LOW);
    return false;
  }
  
}



char sdProcessChar(char character) {
  
    switch (character) {
        case 'A': // 5min
        case 'S': // 15min
        case 'F': // 30min
        case 'G': // 1hr
        case 'H': // 2hr
        case 'J': // 4hr
        case 'K': // 12hr
        case 'L': // 24hr
        case 'a': // 512 blocks
             
            fileSize = character;
            SDfileOpen = setupSDcard(character);
            break;
            
        case 'j': // close the file, if it's open
            if(SDfileOpen){

                SDfileOpen = closeSDfile();
            }
            if(board.streaming)board.streamStop(); // Stop streamming 
            break;
            
        case 's':
            if(SDfileOpen) {
              
                stampSD(ACTIVATE);
            }
            break;
            
        case 'b':
            if(SDfileOpen) {
                stampSD(DEACTIVATE);
            } 
            break;

        case 'c':
        	   // Consider 8-Channels - Single Cyton Board
            BLOCK_DIV = 2;
            break;
            
         case 'C': 
            // Consider 16-Channels - Daisy attached on Cyton Board
            BLOCK_DIV = 1;
            break;
            
        default:
            break;
        
    }

    return character;

}


boolean setupSDcard(char limit){
    
  if(!cardInit){
      if(!card.init(SPI_FULL_SPEED, SD_SS)) {
        if(!board.streaming) {
          Serial0.println("initialization failed. Things to check:");
          Serial0.println("* is a card is inserted?");
        }
      //    card.init(SPI_FULL_SPEED, SD_SS);
      } else {
        if(!board.streaming) {
          Serial0.println("Wiring is correct and a card is present.");
        }
        cardInit = true;
      }
      if (!volume.init(card)) { // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
        if(!board.streaming) {
          Serial0.println("Could not find FAT16/FAT32 partition. Make sure you've formatted the card");
          board.sendEOT();
        }
        return fileIsOpen;
      }
   }


       
  // use limit to determine file size
  switch(limit){
    case 'h':
      BLOCK_COUNT = 50/BLOCK_DIV; break;
    case 'a':
      BLOCK_COUNT = 512/BLOCK_DIV; break;
    case 'A':
      BLOCK_COUNT = BLOCK_5MIN/BLOCK_DIV; break;
    case 'S':
      BLOCK_COUNT = BLOCK_15MIN/BLOCK_DIV; break;
    case 'F':
      BLOCK_COUNT = BLOCK_30MIN/BLOCK_DIV; break;
    case 'G':
      BLOCK_COUNT = BLOCK_1HR/BLOCK_DIV; break;
    case 'H':
      BLOCK_COUNT = BLOCK_2HR/BLOCK_DIV; break;
    case 'J':
      BLOCK_COUNT = BLOCK_4HR/BLOCK_DIV; break;
    case 'K':
      BLOCK_COUNT = BLOCK_12HR/BLOCK_DIV; break;
    case 'L':
      BLOCK_COUNT = BLOCK_24HR/BLOCK_DIV; break;
    default:
      if(!board.streaming) {
        Serial0.println("invalid BLOCK count");
        board.sendEOT(); // Write end of transmission because we exit here
      }
      return fileIsOpen;
  }

 
  incrementFileCounter();
  openvol = root.openRoot(volume);
  openfile.remove(root, currentFileName); // if the file is over-writing, let it!

  if (!openfile.createContiguous(root, currentFileName, BLOCK_COUNT*512UL)) {
    if(!board.streaming) {
      Serial0.print("createfdContiguous fail");
      LED_SD_Status_Indication(ERROR_BLINKS, 500, ERROR_LED);
      
    }
    cardInit = false;
  }//else{Serial0.print("got contiguous file...");delay(1);}
  // get the location of the file's blocks
  if (!openfile.contiguousRange(&bgnBlock, &endBlock)) {
    if(!board.streaming) {
      Serial0.print("get contiguousRange fail");
      LED_SD_Status_Indication(ERROR_BLINKS, 500, ERROR_LED);
   
    }
    cardInit = false;
  }//else{Serial0.print("got file range...");delay(1);}
  
  // grab the Cache
  pCache = (uint8_t*)volume.cacheClear();
  
  // tell card to setup for multiple block write with pre-erase
  if (!card.erase(bgnBlock, endBlock)){
    if(!board.streaming) {
      Serial0.println("erase block fail");
      LED_SD_Status_Indication(ERROR_BLINKS, 500, ERROR_LED);
    }
    cardInit = false;
  }//else{Serial0.print("erased...");delay(1);}
 
  if (!card.writeStart(bgnBlock, BLOCK_COUNT)){
    if(!board.streaming) {
      Serial0.println("writeStart fail");
      LED_SD_Status_Indication(ERROR_BLINKS, 500, ERROR_LED);
    }
    cardInit = false;
  } else{
    fileIsOpen = true;
    delay(1);
  }
  board.csHigh(SD_SS);  // release the spi
  
  // initialize write-time overrun error counter and min/max wirte time benchmarks
  overruns = 0;
  maxWriteTime = 0;
  minWriteTime = 65000;
  byteCounter = 0;  // counter from 0 - 512
  blockCounter = 0; // counter from 0 - BLOCK_COUNT;
  if(fileIsOpen == true){  // send corresponding file name to controlling program
    if(!board.streaming) {
      Serial0.print("Corresponding SD file ");
      Serial0.println(currentFileName);
      LED_SD_Status_Indication(OK_BLINKS, 250, OK_LED);
    }
  }
  if(!board.streaming) {
    board.sendEOT();
  }
  return fileIsOpen;
}






boolean closeSDfile(){

  if(fileIsOpen){
    board.csLow(SD_SS);  // take spi
    card.writeStop();
    openfile.close();
    board.csHigh(SD_SS);  // release the spi
    fileIsOpen = false;
    if(!board.streaming){ // verbosity. this also gets insterted as footer in openFile
      Serial0.print("SamplingRate: ");Serial0.print(board.getSampleRate());Serial0.println("Hz"); //delay(10);
      Serial0.print("Total Elapsed Time: ");Serial0.print(t);Serial0.println(" mS");              //delay(10);
      Serial0.print("Max write time: "); Serial0.print(maxWriteTime); Serial0.println(" uS");     //delay(10);
      Serial0.print("Min write time: ");Serial0.print(minWriteTime); Serial0.println(" uS");      //delay(10);
      Serial0.print("Overruns: "); Serial0.print(overruns); Serial0.println(); //delay(10);
      if (overruns) {
        uint8_t n = overruns > OVER_DIM ? OVER_DIM : overruns;
        Serial0.println("fileBlock,micros");
        for (uint8_t i = 0; i < n; i++) {
          Serial0.print(over[i].block); Serial0.print(','); Serial0.println(over[i].micro);
        }
        
      }
      board.sendEOT();
    }


  }else{
    if(!board.streaming) {
      Serial0.println("No open file to close");
      board.sendEOT();
    }
    
  }
  
  // delay(100); // cool down
  return fileIsOpen;
}



void writeDataToSDcard(byte sampleNumber){
  boolean addComma = true;
  // convert 8 bit sampleCounter into HEX
  convertToHex(sampleNumber, 1, addComma);
  // convert 24 bit channelData into HEX
  for (int currentChannel = 0; currentChannel < 8; currentChannel++){
    convertToHex(board.boardChannelDataInt[currentChannel], 5, addComma);
    
    // If Daisy Is NOT Attached -> stop putting comma delimiter at 7th sample 
    if(board.daisyPresent == false){
      if(currentChannel == 6){
        addComma = false;
        if(addAuxToSD || addAccelToSD) { addComma = true; }  // format CSV
      }
    }
    
   } 

   // If Daisy Is Attached -> stop putting comma delimiter at 7th sample
  if(board.daisyPresent){
    for (int currentChannel = 0; currentChannel < 8; currentChannel++){
      convertToHex(board.daisyChannelDataInt[currentChannel], 5, addComma);
      if(currentChannel == 6){
        addComma = false;
        if(addAuxToSD || addAccelToSD) {addComma = true;}  // format CSV
      }
    }
    
  }

  

  if(addAuxToSD == true){
    // convert auxData into HEX
    for(int currentChannel = 0; currentChannel <  3; currentChannel++){
      convertToHex(board.auxData[currentChannel], 3, addComma);
      if(currentChannel == 1) addComma = false;
    }
    addAuxToSD = false;
  }// end of aux data log

  
  else if(addAccelToSD == true){  // if we have accelerometer data to log
    // convert 16 bit accelerometer data into HEX
    for (int currentChannel = 0; currentChannel < 3; currentChannel++){
      convertToHex(board.axisData[currentChannel], 3, addComma);
      if(currentChannel == 1) addComma = false;
    }
    addAccelToSD = false;  // reset addAccel
  }// end of accelerometer data log

   // add aux data logging...
}



void writeCache(){
    
    if(blockCounter > BLOCK_COUNT) {
      blockCounter=0; 
      return;
    }
    
    uint32_t tw = micros();  // start block write timer
    board.csLow(SD_SS);  // take spi
    if(!card.writeData(pCache)) {
      if (!board.streaming) {
        Serial0.println("block write fail");
        board.sendEOT();
      }
    }   // write the block
    board.csHigh(SD_SS);  // release spi
    tw = micros() - tw;      // stop block write timer
    if (tw > maxWriteTime) maxWriteTime = tw;  // check for max write time
    if (tw < minWriteTime) minWriteTime = tw;  // check for min write time
    if (tw > MICROS_PER_BLOCK) {      // check for overrun
    if (overruns < OVER_DIM) {
        over[overruns].block = blockCounter;
        over[overruns].micro = tw;
      }
      overruns++;
    }

    byteCounter = 0; // reset 512 byte counter for next block
    blockCounter++;    // increment BLOCK counter
    
    if(blockCounter == BLOCK_COUNT-1){
      t = millis() - t;

      // Time to Close the file but do not stop Streaming 
      writeFooter();
    }
    
    if(blockCounter == BLOCK_COUNT){
       SDfileOpen  = closeSDfile(); // Update open-file flag     
    }  // we did it!
    
}


void incrementFileCounter(){
  
  fileTens = EEPROM.read(0);
  fileOnes = EEPROM.read(1);
 
  // if it's the first time writing to EEPROM, seed the file number to '00'
  if(fileTens == 0xFF | fileOnes == 0xFF){
    fileTens = fileOnes = '0';
  }
  fileOnes++;   // increment the file name
  if (fileOnes == ':'){fileOnes = 'A';}
  if (fileOnes > 'F'){
    fileOnes = '0';         // hexify
    fileTens++;
    if(fileTens == ':'){fileTens = 'A';}
    if(fileTens > 'F'){fileTens = '0';fileOnes = '1';}
  }
  EEPROM.write(0,fileTens);     // store current file number in eeprom
  EEPROM.write(1,fileOnes);
  currentFileName[5] = fileTens;
  currentFileName[6] = fileOnes;
   //  // send corresponding file name to controlling program
   //  Serial0.print("Corresponding SD file ");Serial0.println(currentFileName);
}






void stampSD(boolean state){

  unsigned long time = millis();
  if(state){
    for(int i=0; i<10; i++){
      pCache[byteCounter] = pgm_read_byte_near(startStamp+i);
      byteCounter++;
      if(byteCounter == 512){
        writeCache();
      }
    }
  }
  else{
    for(int i=0; i<9; i++){
      pCache[byteCounter] = pgm_read_byte_near(stopStamp+i);
      byteCounter++;
      if(byteCounter == 512){
        writeCache();
      }
    }
  }
  convertToHex(time, 7, false);
}




void writeFooter(){
 
  for(int i=0; i<16; i++){
    pCache[byteCounter] = pgm_read_byte_near(samplingFreq+i);
    byteCounter++;
  }
  String daqFreq = board.getSampleRate();
  convertToHex(daqFreq.toInt(), 4, false);
  
  for(int i=0; i<17; i++){
    pCache[byteCounter] = pgm_read_byte_near(elapsedTime+i);
    byteCounter++;
  }
  convertToHex(t, 7, false);

  for(int i=0; i<20; i++){
    pCache[byteCounter] = pgm_read_byte_near(minTime+i);
    byteCounter++;
  }
  convertToHex(minWriteTime, 7, false);

  for(int i=0; i<20; i++){
    pCache[byteCounter] = pgm_read_byte_near(maxTime+i);
    byteCounter++;
  }
  convertToHex(maxWriteTime, 7, false);

  for(int i=0; i<7; i++){
    pCache[byteCounter] = pgm_read_byte_near(overNum+i);
    byteCounter++;
  }
  convertToHex(overruns, 7, false);

  for(int i=0; i<11; i++){
    pCache[byteCounter] = pgm_read_byte_near(blockTime+i);
    byteCounter++;
  }

  if (overruns) {
    uint8_t n = overruns > OVER_DIM ? OVER_DIM : overruns;
    for (uint8_t i = 0; i < n; i++) {
      convertToHex(over[i].block, 7, true);
      convertToHex(over[i].micro, 7, false);
    }
  }

  for(int i=byteCounter; i<512; i++){
    pCache[i] = NULL;
  }
 
  writeCache();
}




//    CONVERT RAW BYTE DATA TO HEX FOR SD STORAGE
void convertToHex(long rawData, int numNibbles, boolean useComma){

  for (int currentNibble = numNibbles; currentNibble >= 0; currentNibble--){
    byte nibble = (rawData >> currentNibble*4) & 0x0F;
    if (nibble > 9){
      nibble += 55;  // convert to ASCII A-F
    }
    else{
      nibble += 48;  // convert to ASCII 0-9
    }
    pCache[byteCounter] = nibble;
    byteCounter++;
    if(byteCounter == 512){
      writeCache();
    }
  }
  if(useComma == true){
    pCache[byteCounter] = ',';
  }else{
    pCache[byteCounter] = '\n';
  }
  byteCounter++;
  if(byteCounter == 512){
    writeCache();
  }
}// end of byteToHex converter
