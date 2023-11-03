
#include "Server.h"
#include "Room.h"
#include "JoinCode.h"
#include "UUIDGenerator.h"

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
using networking::Message;
using server_model::Room;

enum class CommandStatus {
    DISCONNECT,
    SHUTDOWN,
    NOTHING
};

struct MessageResult {
    std::string result;
    bool shouldShutdown;
};

struct UserData {
    Room* room{nullptr};
    std::vector<std::string> messagesFromServer;
};

class ChatServer {
private:
    std::vector<Room> rooms;
    std::unordered_map<Connection, UserData> connectionUserMap;
    Server server;
    JoinCodeGenerator joinCodeGen;
    UUIDGenerator uuidGenerator;
    
    void connectUser(Connection c);
    void disconnectUser(Connection c);
    
    std::vector<std::string> splitString(const std::string& text);
    std::string createRoom(const Message& message);
    std::string joinRoom(const Message& message);
    std::string leaveRoom(const Connection& c);
    CommandStatus handleCommand(const Message& message);
    MessageResult processMessages(const std::deque<Message>& incoming);

    void sendUserServerMessage(Message message, const std::string& log);
    std::deque<Message> buildOutgoing(const std::string& log);
    std::deque<Message> buildOutgoingPrivateServerMsg();

    void printUsersAndRooms();

public:
    ChatServer(unsigned short port, std::string httpMessage, JoinCodeGenerator joinCodeGen, UUIDGenerator uuidGenerator);
    bool update();
    static std::string getHTTPMessage(const char* htmlLocation);
    static std::string timeString();

};


