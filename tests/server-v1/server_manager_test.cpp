#include <gtest/gtest.h>
#include "ServerManager.h"
// Demonstrate some basic assertions.
TEST(serverTest, BasicAssertions)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world!");
    // Expect equality.
    EXPECT_EQ(25 * 2, 50);
}

TEST(ServerManager, BasicInstance)
{
    ServerManager serverManager{};
    EXPECT_TRUE(serverManager.ping());
}
