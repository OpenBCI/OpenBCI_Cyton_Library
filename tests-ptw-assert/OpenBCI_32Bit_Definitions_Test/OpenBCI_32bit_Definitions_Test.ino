#include <DSPI.h>
#include <EEPROM.h>
#include "OpenBCI_32bit.h"

void setup() {
  // put your setup code here, to run once:
//  Serial0.begin(115200);
  board.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (board.isSerialAvailableForRead()) {
    char newChar = board.readOneSerialChar();
    test();
  }
}

void test() {
  boolean allTestsPassed = true;
  Serial0.println("\nTests Begin\n");

  // allTestsPassed = testTurningChannelsOff() && allTestsPassed;
  // allTestsPassed = testTurningChannelsOn() && allTestsPassed;
  // allTestsPassed = testChannelSettingCommands() && allTestsPassed;
  allTestsPassed = testTestSignalControlCommands() && allTestsPassed;

  if (allTestsPassed) {
    Serial0.println("\nAll tests passed!");
  }

  Serial0.println("\nTests End\n");
}

// boolean testTurningChannelsOff(void) {
//   boolean allTestsPassed = true;
//   boolean passed;
//
//   Serial0.println("#TurningChannelsOff");
//
//   passed = assertEqualChar('1', OPENBCI_CHANNEL_OFF_1);
//   verbosePrintResult2(passed,"Channel 1");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('2', OPENBCI_CHANNEL_OFF_2);
//   verbosePrintResult2(passed,"Channel 2");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('3', OPENBCI_CHANNEL_OFF_3);
//   verbosePrintResult2(passed,"Channel 3");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('4', OPENBCI_CHANNEL_OFF_4);
//   verbosePrintResult2(passed,"Channel 4");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('5', OPENBCI_CHANNEL_OFF_5);
//   verbosePrintResult2(passed,"Channel 5");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('6', OPENBCI_CHANNEL_OFF_6);
//   verbosePrintResult2(passed,"Channel 6");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('7', OPENBCI_CHANNEL_OFF_7);
//   verbosePrintResult2(passed,"Channel 7");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('8', OPENBCI_CHANNEL_OFF_8);
//   verbosePrintResult2(passed,"Channel 8");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('q', OPENBCI_CHANNEL_OFF_9);
//   verbosePrintResult2(passed,"Channel 9");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('w', OPENBCI_CHANNEL_OFF_10);
//   verbosePrintResult2(passed,"Channel 10");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('e', OPENBCI_CHANNEL_OFF_11);
//   verbosePrintResult2(passed,"Channel 11");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('r', OPENBCI_CHANNEL_OFF_12);
//   verbosePrintResult2(passed,"Channel 12");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('t', OPENBCI_CHANNEL_OFF_13);
//   verbosePrintResult2(passed,"Channel 13");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('y', OPENBCI_CHANNEL_OFF_14);
//   verbosePrintResult2(passed,"Channel 14");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('u', OPENBCI_CHANNEL_OFF_15);
//   verbosePrintResult2(passed,"Channel 15");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('i', OPENBCI_CHANNEL_OFF_16);
//   verbosePrintResult2(passed,"Channel 16");
//   if (!passed) allTestsPassed = false;
//
//   return allTestsPassed;
// }
//
// boolean testTurningChannelsOn(void) {
//   boolean allTestsPassed = true;
//   boolean passed;
//
//   Serial0.println("#TurningChannelsOn");
//
//   passed = assertEqualChar('!', OPENBCI_CHANNEL_ON_1);
//   verbosePrintResult2(passed,"Channel 1");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('@', OPENBCI_CHANNEL_ON_2);
//   verbosePrintResult2(passed,"Channel 2");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('#', OPENBCI_CHANNEL_ON_3);
//   verbosePrintResult2(passed,"Channel 3");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('$', OPENBCI_CHANNEL_ON_4);
//   verbosePrintResult2(passed,"Channel 4");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('%', OPENBCI_CHANNEL_ON_5);
//   verbosePrintResult2(passed,"Channel 5");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('^', OPENBCI_CHANNEL_ON_6);
//   verbosePrintResult2(passed,"Channel 6");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('&', OPENBCI_CHANNEL_ON_7);
//   verbosePrintResult2(passed,"Channel 7");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('*', OPENBCI_CHANNEL_ON_8);
//   verbosePrintResult2(passed,"Channel 8");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('Q', OPENBCI_CHANNEL_ON_9);
//   verbosePrintResult2(passed,"Channel 9");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('W', OPENBCI_CHANNEL_ON_10);
//   verbosePrintResult2(passed,"Channel 10");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('E', OPENBCI_CHANNEL_ON_11);
//   verbosePrintResult2(passed,"Channel 11");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('R', OPENBCI_CHANNEL_ON_12);
//   verbosePrintResult2(passed,"Channel 12");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('T', OPENBCI_CHANNEL_ON_13);
//   verbosePrintResult2(passed,"Channel 13");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('Y', OPENBCI_CHANNEL_ON_14);
//   verbosePrintResult2(passed,"Channel 14");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('U', OPENBCI_CHANNEL_ON_15);
//   verbosePrintResult2(passed,"Channel 15");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('I', OPENBCI_CHANNEL_ON_16);
//   verbosePrintResult2(passed,"Channel 16");
//   if (!passed) allTestsPassed = false;
//
//   return allTestsPassed;
// }
//
// boolean testChannelSettingCommands() {
//   boolean allTestsPassed = true;
//   boolean passed;
//
//   Serial0.println("#ChannelSettingCommands");
//
//   passed = assertEqualChar('1', OPENBCI_CHANNEL_CMD_CHANNEL_1);
//   verbosePrintResult2(passed,"Channel 1");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('2', OPENBCI_CHANNEL_CMD_CHANNEL_2);
//   verbosePrintResult2(passed,"Channel 2");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('3', OPENBCI_CHANNEL_CMD_CHANNEL_3);
//   verbosePrintResult2(passed,"Channel 3");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('4', OPENBCI_CHANNEL_CMD_CHANNEL_4);
//   verbosePrintResult2(passed,"Channel 4");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('5', OPENBCI_CHANNEL_CMD_CHANNEL_5);
//   verbosePrintResult2(passed,"Channel 5");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('6', OPENBCI_CHANNEL_CMD_CHANNEL_6);
//   verbosePrintResult2(passed,"Channel 6");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('7', OPENBCI_CHANNEL_CMD_CHANNEL_7);
//   verbosePrintResult2(passed,"Channel 7");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('8', OPENBCI_CHANNEL_CMD_CHANNEL_8);
//   verbosePrintResult2(passed,"Channel 8");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('Q', OPENBCI_CHANNEL_CMD_CHANNEL_9);
//   verbosePrintResult2(passed,"Channel 9");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('W', OPENBCI_CHANNEL_CMD_CHANNEL_10);
//   verbosePrintResult2(passed,"Channel 10");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('E', OPENBCI_CHANNEL_CMD_CHANNEL_11);
//   verbosePrintResult2(passed,"Channel 11");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('R', OPENBCI_CHANNEL_CMD_CHANNEL_12);
//   verbosePrintResult2(passed,"Channel 12");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('T', OPENBCI_CHANNEL_CMD_CHANNEL_13);
//   verbosePrintResult2(passed,"Channel 13");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('Y', OPENBCI_CHANNEL_CMD_CHANNEL_14);
//   verbosePrintResult2(passed,"Channel 14");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('U', OPENBCI_CHANNEL_CMD_CHANNEL_15);
//   verbosePrintResult2(passed,"Channel 15");
//   if (!passed) allTestsPassed = false;
//
//   passed = assertEqualChar('I', OPENBCI_CHANNEL_CMD_CHANNEL_16);
//   verbosePrintResult2(passed,"Channel 16");
//   if (!passed) allTestsPassed = false;
//
//   return allTestsPassed;
// }

boolean testTestSignalControlCommands(void) {
  boolean allTestsPassed = true;
  boolean passed;

  Serial0.println("#TestSignalControlCommands");

  passed = assertEqualChar('p', OPENBCI_TEST_SIGNAL_CONNECT_TO_DC);
  verbosePrintResult2(passed,"Connect to DC");
  if (!passed) allTestsPassed = false;

  passed = assertEqualChar('0', OPENBCI_TEST_SIGNAL_CONNECT_TO_GROUND);
  verbosePrintResult2(passed,"Connect to Ground");
  if (!passed) allTestsPassed = false;

  passed = assertEqualChar('=', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_1X_FAST);
  verbosePrintResult2(passed,"Pulse 1x Fast");
  if (!passed) allTestsPassed = false;

  passed = assertEqualChar('-', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_1X_SLOW);
  verbosePrintResult2(passed,"Pulse 1x Slow");
  if (!passed) allTestsPassed = false;

  passed = assertEqualChar(']', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_2X_FAST);
  verbosePrintResult2(passed,"Pulse 2x Fast");
  if (!passed) allTestsPassed = false;

  passed = assertEqualChar('[', OPENBCI_TEST_SIGNAL_CONNECT_TO_PULSE_2X_SLOW);
  verbosePrintResult2(passed,"Pulse 2x Slow");
  if (!passed) allTestsPassed = false;

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
     Serial0.print("  Passed - ");
     Serial0.print(testName);
     Serial0.print(" - ");
     Serial0.println(msg);
   } else  {
     Serial0.print("  ****Failed - ");
     Serial0.print(testName);
     Serial0.print(" - ");
     Serial0.println(msg);
   }
}

void verbosePrintResult2(boolean testPassed, char *msg) {
   if (testPassed) {
     Serial0.print("  Passed - ");
     Serial0.println(msg);
   } else  {
     Serial0.print("  ****Failed - ");
     Serial0.println(msg);
   }
}
