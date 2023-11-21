#include "Room.h"

#include "ServerManager.h"


Room::Room(ServerManager &serverManager) : serverManager(serverManager)
{
}


void Room::ping()
{
    serverManager.ping();
}


bool Room::roomPing()
{
    return true;
}