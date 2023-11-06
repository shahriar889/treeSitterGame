#pragma once

#include "ServerManager.h"

//remove should not know about any server/Server.h details 
class Room {

    public:
    Room(ServerManager &serverManager);
    void ping ();
    bool roomPing();


    private:

    ServerManager &serverManager;


};




