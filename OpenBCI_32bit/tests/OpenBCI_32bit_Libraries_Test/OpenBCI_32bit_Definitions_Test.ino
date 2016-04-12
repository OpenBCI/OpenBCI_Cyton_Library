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

  allTestsPassed = testTurningChannelsOff() && allTestsPassed;
  allTestsPassed = testTurningChannelsOn() && allTestsPassed;
  allTestsPassed = testChannelSettingCommands() && allTestsPassed;
  allTestsPassed = testTestSignalControlCommands() && allTestsPassed;

  if (allTestsPassed) {
    Serial.println("\nAll tests passed!");
  }

  Serial.println("\nTests End\n");
}

boolean testTurningChannelsOff(void) {
  boolean allTestsPassed = true;
  boolean passed;

  passed = assertEqualChar('1', OPENBCI_CHANNEL_OFF_1) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 1"); allTestsPassed = false;
  passed = assertEqualChar('2', OPENBCI_CHANNEL_OFF_2) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 2"); allTestsPassed = false;
  passed = assertEqualChar('3', OPENBCI_CHANNEL_OFF_3) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 3"); allTestsPassed = false;
  passed = assertEqualChar('4', OPENBCI_CHANNEL_OFF_4) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 4"); allTestsPassed = false;
  passed = assertEqualChar('5', OPENBCI_CHANNEL_OFF_5) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 5"); allTestsPassed = false;
  passed = assertEqualChar('6', OPENBCI_CHANNEL_OFF_6) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 6"); allTestsPassed = false;
  passed = assertEqualChar('7', OPENBCI_CHANNEL_OFF_7) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 7"); allTestsPassed = false;
  passed = assertEqualChar('8', OPENBCI_CHANNEL_OFF_8) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 8"); allTestsPassed = false;

  passed = assertEqualChar('q', OPENBCI_CHANNEL_OFF_9) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 9"); allTestsPassed = false;
  passed = assertEqualChar('w', OPENBCI_CHANNEL_OFF_10) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 10"); allTestsPassed = false;
  passed = assertEqualChar('e', OPENBCI_CHANNEL_OFF_11) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 11"); allTestsPassed = false;
  passed = assertEqualChar('r', OPENBCI_CHANNEL_OFF_12) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 12"); allTestsPassed = false;
  passed = assertEqualChar('t', OPENBCI_CHANNEL_OFF_13) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 13"); allTestsPassed = false;
  passed = assertEqualChar('y', OPENBCI_CHANNEL_OFF_14) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 14"); allTestsPassed = false;
  passed = assertEqualChar('u', OPENBCI_CHANNEL_OFF_15) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 15"); allTestsPassed = false;
  passed = assertEqualChar('i', OPENBCI_CHANNEL_OFF_16) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOff","Channel 16"); allTestsPassed = false;

  return allTestsPassed;
}

boolean testTurningChannelsOn(void) {
  boolean allTestsPassed = true;
  boolean passed;

  passed = assertEqualChar('!', OPENBCI_CHANNEL_ON_1) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 1"); allTestsPassed = false;
  passed = assertEqualChar('@', OPENBCI_CHANNEL_ON_2) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 2"); allTestsPassed = false;
  passed = assertEqualChar('#', OPENBCI_CHANNEL_ON_3) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 3"); allTestsPassed = false;
  passed = assertEqualChar('$', OPENBCI_CHANNEL_ON_4) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 4"); allTestsPassed = false;
  passed = assertEqualChar('%', OPENBCI_CHANNEL_ON_5) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 5"); allTestsPassed = false;
  passed = assertEqualChar('^', OPENBCI_CHANNEL_ON_6) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 6"); allTestsPassed = false;
  passed = assertEqualChar('&', OPENBCI_CHANNEL_ON_7) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 7"); allTestsPassed = false;
  passed = assertEqualChar('*', OPENBCI_CHANNEL_ON_8) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 8"); allTestsPassed = false;

  passed = assertEqualChar('Q', OPENBCI_CHANNEL_ON_9) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 9"); allTestsPassed = false;
  passed = assertEqualChar('W', OPENBCI_CHANNEL_ON_10) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 10"); allTestsPassed = false;
  passed = assertEqualChar('E', OPENBCI_CHANNEL_ON_11) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 11"); allTestsPassed = false;
  passed = assertEqualChar('R', OPENBCI_CHANNEL_ON_12) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 12"); allTestsPassed = false;
  passed = assertEqualChar('T', OPENBCI_CHANNEL_ON_13) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 13"); allTestsPassed = false;
  passed = assertEqualChar('Y', OPENBCI_CHANNEL_ON_14) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 14"); allTestsPassed = false;
  passed = assertEqualChar('U', OPENBCI_CHANNEL_ON_15) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 15"); allTestsPassed = false;
  passed = assertEqualChar('I', OPENBCI_CHANNEL_ON_16) && passed;
  if (!passed) verbosePrintResult(passed,"TurningChannelsOn","Channel 16"); allTestsPassed = false;

  return allTestsPassed;
}

boolean testChannelSettingCommands() {
  boolean allTestsPassed = true;
  boolean passed;

  passed = assertEqualChar('1', OPENBCI_CHANNEL_CMD_CHANNEL_1) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 1"); allTestsPassed = false;
  passed = assertEqualChar('2', OPENBCI_CHANNEL_CMD_CHANNEL_2) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 2"); allTestsPassed = false;
  passed = assertEqualChar('3', OPENBCI_CHANNEL_CMD_CHANNEL_3) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 3"); allTestsPassed = false;
  passed = assertEqualChar('4', OPENBCI_CHANNEL_CMD_CHANNEL_4) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 4"); allTestsPassed = false;
  passed = assertEqualChar('5', OPENBCI_CHANNEL_CMD_CHANNEL_5) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 5"); allTestsPassed = false;
  passed = assertEqualChar('6', OPENBCI_CHANNEL_CMD_CHANNEL_6) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 6"); allTestsPassed = false;
  passed = assertEqualChar('7', OPENBCI_CHANNEL_CMD_CHANNEL_7) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 7"); allTestsPassed = false;
  passed = assertEqualChar('8', OPENBCI_CHANNEL_CMD_CHANNEL_8) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 8"); allTestsPassed = false;

  passed = assertEqualChar('Q', OPENBCI_CHANNEL_CMD_CHANNEL_9) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 9"); allTestsPassed = false;
  passed = assertEqualChar('W', OPENBCI_CHANNEL_CMD_CHANNEL_10) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 10"); allTestsPassed = false;
  passed = assertEqualChar('E', OPENBCI_CHANNEL_CMD_CHANNEL_11) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 11"); allTestsPassed = false;
  passed = assertEqualChar('R', OPENBCI_CHANNEL_CMD_CHANNEL_12) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 12"); allTestsPassed = false;
  passed = assertEqualChar('T', OPENBCI_CHANNEL_CMD_CHANNEL_13) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 13"); allTestsPassed = false;
  passed = assertEqualChar('Y', OPENBCI_CHANNEL_CMD_CHANNEL_14) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 14"); allTestsPassed = false;
  passed = assertEqualChar('U', OPENBCI_CHANNEL_CMD_CHANNEL_15) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 15"); allTestsPassed = false;
  passed = assertEqualChar('I', OPENBCI_CHANNEL_CMD_CHANNEL_16) && passed;
  if (!passed) verbosePrintResult(passed,"Consts Check","Channel 16"); allTestsPassed = false;

  return allTestsPassed;
}

boolean testTestSignalControlCommands(void) {
  boolean allTestsPassed = true;
  boolean passed;

  passed = assertEqualChar('0', OPENBCI_TEST_SIGNAL_CONNECT_TO_DC);
  if (!passed) verbosePrintResult(passed,"Test Signal","DC"); allTestsPassed = false;
  passed = assertEqualChar('p', OPENBCI_TEST_SIGNAL_CONNECT_TO_GROUND);
  if (!passed) verbosePrintResult(passed,"Test Signal","Ground"); allTestsPassed = false;
  passed = assertEqualChar('=', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_1X_FAST);
  if (!passed) verbosePrintResult(passed,"Test Signal","1x Fast"); allTestsPassed = false;
  passed = assertEqualChar('-', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_1X_SLOW);
  if (!passed) verbosePrintResult(passed,"Test Signal","1x Slow"); allTestsPassed = false;
  passed = assertEqualChar(']', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_2X_FAST);
  if (!passed) verbosePrintResult(result,"Test Signal","2x Fast"); allTestsPassed = false;
  passed = assertEqualChar('[', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_2X_SLOW);
  if (!passed) verbosePrintResult(passed,"Test Signal","2x Slow"); allTestsPassed = false;

  return allTestsPassed;
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
