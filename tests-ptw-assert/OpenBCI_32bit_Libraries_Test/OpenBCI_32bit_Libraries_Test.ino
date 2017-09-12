#include <DSPI.h>
#include <EEPROM.h>
#include "OpenBCI_32bit.h"
#include "PTW-Arduino-Assert.h"

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  test.setSerial(Serial1);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()) {
    Serial1.read();
    go();
  }
}

void go() {
  // Start the test
  test.begin();

  // testGetters();
  // testResets();
  // testSendChannelData();

  test.end();
}

void testGetters() {
    testGetChannelCommandForAsciiChar();
    testGetYesOrNoForAsciiChar();
    testGetGainForAsciiChar();
    testGetNumberForAsciiChar();
    testGetDefaultChannelSettingForSetting();
    testGetDefaultChannelSettingForSettingAscii();
    testGetConstrainedChannelNumber();
    testGetTargetSSForChannelNumber();
}

// void testResets() {
//     testResetChannelSettingsArrayToDefault();
//     testResetLeadOffArrayToDefault();
// }


void testGetChannelCommandForAsciiChar() {

    test.describe("getChannelCommandForAsciiChar");

    test.assertEqual(board.getChannelCommandForAsciiChar('1'),0x00,"Channel 1");
    test.assertEqual(board.getChannelCommandForAsciiChar('2'),0x01,"Channel 2");
    test.assertEqual(board.getChannelCommandForAsciiChar('3'),0x02,"Channel 3");
    test.assertEqual(board.getChannelCommandForAsciiChar('4'),0x03,"Channel 4");
    test.assertEqual(board.getChannelCommandForAsciiChar('5'),0x04,"Channel 5");
    test.assertEqual(board.getChannelCommandForAsciiChar('6'),0x05,"Channel 6");
    test.assertEqual(board.getChannelCommandForAsciiChar('7'),0x06,"Channel 7");
    test.assertEqual(board.getChannelCommandForAsciiChar('8'),0x07,"Channel 8");
    test.assertEqual(board.getChannelCommandForAsciiChar('Q'),0x08,"Channel 9");
    test.assertEqual(board.getChannelCommandForAsciiChar('W'),0x09,"Channel 10");
    test.assertEqual(board.getChannelCommandForAsciiChar('E'),0x0A,"Channel 11");
    test.assertEqual(board.getChannelCommandForAsciiChar('R'),0x0B,"Channel 12");
    test.assertEqual(board.getChannelCommandForAsciiChar('T'),0x0C,"Channel 13");
    test.assertEqual(board.getChannelCommandForAsciiChar('Y'),0x0D,"Channel 14");
    test.assertEqual(board.getChannelCommandForAsciiChar('U'),0x0E,"Channel 15");
    test.assertEqual(board.getChannelCommandForAsciiChar('I'),0x0F,"Channel 16");

}

void testGetYesOrNoForAsciiChar() {

    test.describe("getYesOrNoForAsciiChar");

    test.assertEqual(board.getYesOrNoForAsciiChar('1'),0x01,"Activate");
    test.assertEqual(board.getYesOrNoForAsciiChar('0'),0x00,"Deactivate");
    test.assertEqual(board.getYesOrNoForAsciiChar('7'),0x00,"Input defaults to deactivate");
}

void testGetGainForAsciiChar() {
    test.describe("getGainForAsciiChar");

    test.assertEqual(board.getGainForAsciiChar('0'),0x00,"Gain x1");
    test.assertEqual(board.getGainForAsciiChar('1'),0x10,"Gain x2");
    test.assertEqual(board.getGainForAsciiChar('2'),0x20,"Gain x4");
    test.assertEqual(board.getGainForAsciiChar('3'),0x30,"Gain x6");
    test.assertEqual(board.getGainForAsciiChar('4'),0x40,"Gain x8");
    test.assertEqual(board.getGainForAsciiChar('5'),0x50,"Gain x12");
    test.assertEqual(board.getGainForAsciiChar('6'),0x60,"Gain x24");
    test.assertEqual(board.getGainForAsciiChar(' '),0x60,"Input < '0' defaults to x24");
    test.assertEqual(board.getGainForAsciiChar('7'),0x60,"Inptu > '6' defaults to x24");

}

void testGetNumberForAsciiChar() {

    test.describe("getNumberForAsciiChar");

    test.assertEqual(board.getNumberForAsciiChar('0'),0x00,"Low end test of 0");
    test.assertEqual(board.getNumberForAsciiChar('9'),0x09,"High end test of 9");
    test.assertEqual(board.getNumberForAsciiChar('5'),0x05,"Middle test of 5");
    test.assertEqual(board.getNumberForAsciiChar(' '),0x00,"Out of bounds, too low, defaults to 0");
    test.assertEqual(board.getNumberForAsciiChar('A'),0x00,"Out of bounds, too high, defaults to 0");
}

void testGetDefaultChannelSettingForSetting() {

    test.describe("getDefaultChannelSettingForSetting");

    test.assertEqual(board.getDefaultChannelSettingForSetting(0),0x00,"Power down setting - NO");
    test.assertEqual(board.getDefaultChannelSettingForSetting(1),0x60,"Gain Setting - x24");
    test.assertEqual(board.getDefaultChannelSettingForSetting(2),0x00,"Input type setting - normal");
    test.assertEqual(board.getDefaultChannelSettingForSetting(3),0x01,"Bias setting - YES");
    test.assertEqual(board.getDefaultChannelSettingForSetting(4),0x01,"SRB2 setting - YES");
    test.assertEqual(board.getDefaultChannelSettingForSetting(5),0x00,"SRB1 setting - NO");
    test.assertEqual(board.getDefaultChannelSettingForSetting(6),0x00,"Defaults setting - NO");
}

void testGetDefaultChannelSettingForSettingAscii() {

    test.describe("getDefaultChannelSettingForSettingAscii");

    test.assertEqual(board.getDefaultChannelSettingForSettingAscii(0),'0',"Power down setting - NO");
    test.assertEqual(board.getDefaultChannelSettingForSettingAscii(1),'6',"Gain Setting - x24");
    test.assertEqual(board.getDefaultChannelSettingForSettingAscii(2),'0',"Input type setting - normal");
    test.assertEqual(board.getDefaultChannelSettingForSettingAscii(3),'1',"Bias setting - YES");
    test.assertEqual(board.getDefaultChannelSettingForSettingAscii(4),'1',"SRB2 setting - YES");
    test.assertEqual(board.getDefaultChannelSettingForSettingAscii(5),'0',"SRB1 setting - NO");
    test.assertEqual(board.getDefaultChannelSettingForSettingAscii(6),'0',"Defaults setting - NO");
}

void testGetConstrainedChannelNumber() {

    test.describe("getConstrainedChannelNumber");

    test.assertEqual(board.getConstrainedChannelNumber(0),0,"Out of bounds - Low end - Constrains to 0");
    test.assertEqual(board.getConstrainedChannelNumber(1),0,"Channel 1 - should return 0");
    test.assertEqual(board.getConstrainedChannelNumber(16),15,"Channel 16 - should return 15");
    test.assertEqual(board.getConstrainedChannelNumber(17),15,"Out of bounds - High end - Constrains to 16");
}

void testGetTargetSSForChannelNumber() {

    test.describe("getTargetSSForConstrainedChannelNumber");

    test.assertEqual(board.getTargetSSForConstrainedChannelNumber(0),8,"Index 0 gets BOARD_ADS (8)");
    test.assertEqual(board.getTargetSSForConstrainedChannelNumber(7),8,"Index 7 gets BOARD_ADS (8)");
    test.assertEqual(board.getTargetSSForConstrainedChannelNumber(8),3,"Index 8 gets DAISY_ADS (3)");
    test.assertEqual(board.getTargetSSForConstrainedChannelNumber(15),3,"Index 15 gets DAISY_ADS (3)");
}


// // TODO: Tests for resetChannelSettingsArrayToDefault
// boolean testResetChannelSettingsArrayToDefault() {
//   boolean allPassed = true;
//
//   Serial.println("#resetChannelSettingsArrayToDefault");
//   // allPassed = testCheckSumMake() && allPassed;
//
//   return allPassed;
// }
// // TODO: Tests for resetLeadOffArrayToDefault
// boolean testResetLeadOffArrayToDefault() {
//   boolean allPassed = true;
//
//   Serial.println("#resetLeadOffArrayToDefault");
//   // allPassed = testCheckSumMake() && allPassed;
//
//   return allPassed;
// }

// TODO: Test sendChannelData
void testSendChannelData() {
    test.describe("sendChannelData");

    // A call to send channel data should send 34 bytes, so we should be
    //  able to verify this by counting how many bytes are returned by
    //  '::sendChannelData()'
    byte expectedNumberOfBytes = 33;

    byte acutalNumberOfBytes = board.sendChannelData();

    Serial1.print("\n");

    test.assertEqual(expectedNumberOfBytes, acutalNumberOfBytes, "Stream packet writes 34 bytes");
}
