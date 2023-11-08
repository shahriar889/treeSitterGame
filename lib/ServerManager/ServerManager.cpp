#include "ServerManager.h"
#include "Room.h"
ServerManager::ServerManager(/* args */)
{
}

ServerManager::~ServerManager()
{
}

bool ServerManager::ping()
{
    return true;
}

void ServerManager::roomPing()
{
    Room room{*this};
    room.ping();
}