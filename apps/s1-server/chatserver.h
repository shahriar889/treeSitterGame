#include "Server.h"
#include "Room.h"
#include "JoinCode.h"

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <chrono>
#include <functional>
#include <random>
#include <ctime>

using networking::Server;
using networking::Connection;
using networking::ConnectionHash;
using networking::Message;
using server_model::Room;

enum class CommandStatus {
    DISCONNECT,
    SHUTDOWN,
    NOTHING
};

/*
    Holds the data associated with a Connection. You can view this as the data
    that's associated with a user. Right now, this data includes the Room a user
    is in and the private messages sent to them by the server.
    When accessing this through connectionUserMap.at(), be sure to store the
    result in either a regular variable or a reference as appropriate!
*/
struct UserData {
    Room* room{nullptr};
    std::vector<std::string> messagesFromServer;
};

class ChatServer {
private:
    std::vector<Room> rooms;
    std::unordered_map<Connection, UserData, ConnectionHash> connectionUserMap;
    Server server;
    JoinCodeGenerator joinCodeGen;
    int roomsGenerated = 0;
    bool printableEvent = true;

    std::ostringstream messagesForNullRoom;
    
    void connectUser(Connection c);
    void disconnectUser(Connection c);
    
    std::vector<std::string> splitString(const std::string& text);
    std::string createRoom(const Message& message);
    std::string joinRoom(const Message& message);
    std::string leaveRoom(const Message& message);
    CommandStatus handleCommand(const Message& message);
    bool processMessages(const std::deque<Message>& incoming);

    void sendUserServerMessage(Message message, const std::string& log);
    std::deque<Message> buildOutgoingNullRoom();
    void resetMessagesForNullRoom();
    std::deque<Message> buildOutgoingPrivateServerMsg();

    void printUsersAndRooms(bool alwaysPrint);

public:
    ChatServer(unsigned short port, std::string httpMessage, JoinCodeGenerator joinCodeGen);
    bool update();
    static std::string getHTTPMessage(const char* htmlLocation);
    static std::string timeString();

};


