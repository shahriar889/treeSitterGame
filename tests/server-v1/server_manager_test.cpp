#include <gtest/gtest.h>
#include "ServerManager.h"
#include "Server.h"
#include "Room.h"
#include "User.h"
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
