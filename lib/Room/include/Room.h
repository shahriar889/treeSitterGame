#pragma once

#include "ServerManager.h"

//room should not know about any server/Server.h details 
// should know about creating game and game api
class Room {

    public:
    Room(ServerManager &serverManager);
    void ping ();
    bool roomPing();


    private:

    ServerManager &serverManager;


};




