/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////

/*
Open a terminal in the folder that holds /web-socket-networking/.
Then run:
mkdir networkbuild
cd networkbuild
cmake ../social-gaming/testserver/web-socket-networking/
make
bin/serverdriver 8000 ../social-gaming/testserver/web-socket-networking/webchat.html
bin/client-ncurses localhost 8000
*/

/*
FIXME

The destructor of User runs when:
- There is a new connection
- The server sends a private message to someome
The destructors of User in the users vector run up to and including the target.
If there are 2 User in the vector and a third one joins, 1's and 2's destructors run.
3's will run, but that's because onConnect() makes a User locally, pushes it to the vector,
    then that User goes out of scope.
Similarly, if there are 3 users and 2 types an invalid command,
    making the server send a message to them, 1's and 2's destructors run.

TODO The creator of the room is an admin. The admin can delete room, kick players, etc.
TODO /roominfo to see who's the admin of the room, room's joincode, etc.
TODO Room isolation: you're in a room, you can only interact with users in that room.
TODO prevent people from connecting twice (ex. click on Connect in webchat.html twice)
TODO separate Server out of ChatServer so you can pass in mocks
TODO separate the update loop out of ChatServer so you can test activity with single functions
*/

#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include "Server.h"
#include "chatserver.h"
#include "JoinCode.h"

using networking::Connection;
using networking::Server;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
                  << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
        return 1;
    }

    JoinCodeGenerator joinCodeGen{100};
    UUIDGenerator uuidGen{100};
    const unsigned short port = std::stoi(argv[1]);
    ChatServer chatServer{port, ChatServer::getHTTPMessage(argv[2]), joinCodeGen, uuidGen};

    while (true) {
        bool stop = chatServer.update();
        if (stop) {
            break;
        }

        sleep(3);
    }

    return 0;
}
