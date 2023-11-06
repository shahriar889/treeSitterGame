#include <gtest/gtest.h>
#include "ServerManager.h"
#include "Server.h"
#include "Room.h"
#include "User.h"
#include "StringHandling.h"
#include <vector>
// Demonstrate some basic assertions.

//test the linkage and build of libraries together
TEST(ServerManager, BasicInstantiation)
{
    ServerManager serverManager{};
    EXPECT_TRUE(serverManager.ping());

    Room room{serverManager};
    EXPECT_TRUE(room.roomPing());

    networking::Connection connection{};
    User user{connection};
    EXPECT_TRUE(user.userPing());


}


TEST(StringProcessing, splitingString){


    std::string test = "hello world";

    std::vector<std::string> str=stringTools::split(test," ");

    EXPECT_EQ(str[0],"hello");
    EXPECT_EQ(str[1],"world");

}
