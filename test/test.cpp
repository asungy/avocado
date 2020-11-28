#include "gtest/gtest.h" 
#include "command.hpp"

TEST(CommandTest, TestFunction)
{
    EXPECT_EQ(42, command::TestFunction());
}
