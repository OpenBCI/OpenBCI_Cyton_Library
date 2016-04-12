#include <DSPI.h>
#include <EEPROM.h>
#include "OpenBCI_32bit.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    Serial.read();
    test(); 
  } 
}

void test() {
  boolean allTestsPassed = true;
  Serial.println("\nTests Begin\n");

  allTestsPassed = testGetChannelCommandForAsciiChar() && allTestsPassed;
  allTestsPassed = testGetYesOrNoForAsciiChar() && allTestsPassed;
  allTestsPassed = testGetGainForAsciiChar() && allTestsPassed;
  allTestsPassed = testGetNumberForAsciiChar() && allTestsPassed;
  allTestsPassed = testGetDefaultChannelSettingForSetting() && allTestsPassed;
  allTestsPassed = testGetDefaultChannelSettingForSettingAscii() && allTestsPassed;
  allTestsPassed = testGetConstrainedChannelNumber() && allTestsPassed;
  allTestsPassed = testGetTargetSSForChannelNumber() && allTestsPassed;
  allTestsPassed = testResetChannelSettingsArrayToDefault() && allTestsPassed;
  allTestsPassed = testResetLeadOffArrayToDefault() && allTestsPassed;

  if (allTestsPassed) {
    Serial.println("\nAll tests passed!");
  }
  
  Serial.println("\nTests End\n");
}

// TODO: Tests for getChannelCommandForAsciiChar
boolean testGetChannelCommandForAsciiChar() {
  boolean allPassed = true;
  
  Serial.println("#getChannelCommandForAsciiChar");
  allPassed = testGetChannelCommandForAsciiChar_ConstsCheck() && allPassed;
    
  return allPassed;
}
// Test to make sure getChannelCommandForAsciiChar returns correct char
boolean testGetChannelCommandForAsciiChar_ConstsCheck() {
  boolean result = true;

  result = assertEqualChar('1', OPENBCI_CHANNEL_CMD_CHANNEL_1) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 1");
  result = assertEqualChar('2', OPENBCI_CHANNEL_CMD_CHANNEL_2) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 2");
  result = assertEqualChar('3', OPENBCI_CHANNEL_CMD_CHANNEL_3) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 3");
  result = assertEqualChar('4', OPENBCI_CHANNEL_CMD_CHANNEL_4) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 4");
  result = assertEqualChar('5', OPENBCI_CHANNEL_CMD_CHANNEL_5) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 5");
  result = assertEqualChar('6', OPENBCI_CHANNEL_CMD_CHANNEL_6) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 6");
  result = assertEqualChar('7', OPENBCI_CHANNEL_CMD_CHANNEL_7) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 7");
  result = assertEqualChar('8', OPENBCI_CHANNEL_CMD_CHANNEL_8) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 8");
  result = assertEqualChar('Q', OPENBCI_CHANNEL_CMD_CHANNEL_9) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 9");
  result = assertEqualChar('W', OPENBCI_CHANNEL_CMD_CHANNEL_10) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 10");
  result = assertEqualChar('E', OPENBCI_CHANNEL_CMD_CHANNEL_11) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 11");
  result = assertEqualChar('R', OPENBCI_CHANNEL_CMD_CHANNEL_12) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 12");
  result = assertEqualChar('T', OPENBCI_CHANNEL_CMD_CHANNEL_13) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 13");
  result = assertEqualChar('Y', OPENBCI_CHANNEL_CMD_CHANNEL_14) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 14");
  result = assertEqualChar('U', OPENBCI_CHANNEL_CMD_CHANNEL_15) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 15");
  result = assertEqualChar('I', OPENBCI_CHANNEL_CMD_CHANNEL_16) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 16");
  result = assertEqualChar('J', 0x00) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Returns  when ASCII not defined");
  
  
  return result; 
}

// TODO: Tests for getYesOrNoForAsciiChar
boolean testGetYesOrNoForAsciiChar() {
  boolean allPassed = true;
  
  Serial.println("#getYesOrNoForAsciiChar");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// Test to make sure getChannelCommandForAsciiChar returns correct char
boolean testGetYesOrNoForAsciiChar_YES() {
  boolean result = true;

  result = assertEqualChar(YES, OPENBCI_CHANNEL_CMD_CHANNEL_1) && result;
  if (!result) verbosePrintResult(result,"Consts Check","Channel 1");

  
  
  return result; 
}
// TODO: Tests for getGainForAsciiChar
boolean testGetGainForAsciiChar() {
  boolean allPassed = true;
  
  Serial.println("#getGainForAsciiChar");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// TODO: Tests for getNumberForAsciiChar
boolean testGetNumberForAsciiChar() {
  boolean allPassed = true;
  
  Serial.println("#getNumberForAsciiChar");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// TODO: Tests for getDefaultChannelSettingForSetting
boolean testGetDefaultChannelSettingForSetting() {
  boolean allPassed = true;
  
  Serial.println("#getDefaultChannelSettingForSetting");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// TODO: Tests for getDefaultChannelSettingForSettingAscii
boolean testGetDefaultChannelSettingForSettingAscii() {
  boolean allPassed = true;
  
  Serial.println("#etDefaultChannelSettingForSettingAscii");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// TODO: Tests for getConstrainedChannelNumber
boolean testGetConstrainedChannelNumber() {
  boolean allPassed = true;
  
  Serial.println("#getConstrainedChannelNumber");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// TODO: Tests for getTargetSSForChannelNumber
boolean testGetTargetSSForChannelNumber() {
  boolean allPassed = true;
  
  Serial.println("#getTargetSSForChannelNumber");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// TODO: Tests for resetChannelSettingsArrayToDefault
boolean testResetChannelSettingsArrayToDefault() {
  boolean allPassed = true;
  
  Serial.println("#resetChannelSettingsArrayToDefault");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}
// TODO: Tests for resetLeadOffArrayToDefault
boolean testResetLeadOffArrayToDefault() {
  boolean allPassed = true;
  
  Serial.println("#resetLeadOffArrayToDefault");
  // allPassed = testCheckSumMake() && allPassed;
    
  return allPassed;
}

// ASSERT FUNCTIONS!
boolean assertEqualBoolean(boolean a, boolean b) {
  return a == b;  
}

boolean assertEqualChar(char a, char b) {
  return a == b;  
}

boolean assertGreaterThanChar(char a, char b) {
  return a > b; 
}

boolean assertLessThanChar(char a, char b) {
  return a < b; 
}

boolean assertNotEqualChar(char a, char b) {
  return a != b;  
}

boolean assertEqualInt(int a, int b) {
  return a == b;  
}

void verbosePrintResult(boolean testPassed, char *testName, char *msg) {
   if (testPassed) {
     Serial.print("  Passed - "); 
     Serial.print(testName);
     Serial.print(" - ");
     Serial.println(msg);
   } else  {
     Serial.print("  ****Failed - ");
     Serial.print(testName);
     Serial.print(" - ");
     Serial.println(msg);  
   } 
}

