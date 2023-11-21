#include "User.h"



User::User(Connection &connection) : connection(connection)
{
}


bool User::userPing()
{
    return true;
}