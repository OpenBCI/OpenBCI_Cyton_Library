#include "gtest/gtest.h"
#include "../OpenBCI32bitLibrary.h"
#include "../OpenBCI32bitLibraryDefinitions.h"
#include "Arduino.h"

using ::testing::Return;

TEST(cmds, getChannel) {
	OpenBCI32bitLibraryClass();
	EXPECT_EQ(board.getChannelCommandForAsciiChar('1'), 0x00) << "Channel 1 cmd incorrect ";
}
