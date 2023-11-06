#pragma once

#include "Server.h"

using networking::Connection;

//knows about the server connection details
//uses it for its uniqueness 
class User{

    public:

    User(Connection &connection);
    bool userPing();

    private:
    
    Connection &connection;//unique to each user

};