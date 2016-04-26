#include "gtest/gtest.h"
#include "../include/OpenBCI_32bit_Library.h"
#include "Arduino.h"

using ::testing::Return;

TEST(cmds, getChannel) {
	EXPECT_EQ(board.getChannelCommandForAsciiChar('1'), 0x00) << "Channel 1 cmd incorrect ";
}