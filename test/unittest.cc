#include "gtest/gtest.h"
#include "Arduino.h"
#include "DSPI.h"
#include "Serial.h"
#include "../OpenBCI_32bit_Library_Definitions.h"
#include "../OpenBCI_32bit_Library.h"


// using ::testing::Return;

TEST(cmds, getChannel) {
	OpenBCI_32bit_Library bciBoard;

	// EXPECT_EQ(bciBoard.getChannelCommandForAsciiChar('1'), 0x00) << "Channel 1 cmd incorrect ";
}
