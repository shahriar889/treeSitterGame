#include "chatserver.h"

ChatServer::ChatServer(unsigned short port, std::string httpMessage,
                       JoinCodeGenerator joinCodeGen)
    : server{Server(port, httpMessage,
        [&] (Connection c) {connectUser(c);},
        [&] (Connection c) {disconnectUser(c);})} 
    , joinCodeGen{joinCodeGen}
    // , connectionUserMap{{}}
{}

void
ChatServer::connectUser(Connection c) {
    printableEvent = true;
    std::cout << timeString();
    std::cout << "New connection found: " << c.id << "\n";

    // Things between < > don't show up on the HTML webpage. Using CAPS instead
    std::string newUserMsg =
        "Welcome new user!\n"
        "Feel free to chat with others in this public room.\n"
        "If you want to create a private room, send \"/createroom --name ROOM_NAME --game ROOM_GAME\".\n"
        "If you want to join a private room, send \"/joinroom JOIN_CODE\".\n";

    UserData user;
    user.messagesFromServer.push_back(newUserMsg);
    bool success = connectionUserMap.insert({c, user}).second;
    if (!success) {
        std::cout << "Failed to insert connection " << c.id << ". Key already exists\n";
    }
}

void
ChatServer::disconnectUser(Connection c) {
    printableEvent = true;
    std::cout << timeString();
    std::cout << "Trying to disconnect " << c.id << "\n";

    // Get the user's room. Delete them from their room.
    UserData user = connectionUserMap.at(c);
    if (user.room) {
        user.room->removeConnection(c);
        std::cout << "disconnectUser: removed connection\n";
    } else {
        std::cout << "disconnectUser: connection has no Room\n";
    }
    
    // Remove the connection
    std::cout << "Num users before delete is " << connectionUserMap.size() << "\n";
    connectionUserMap.erase(c);
    std::cout << "Num users after delete is " << connectionUserMap.size() << "\n";

    std::cout << "Connection lost: " << c.id << "\n";
}

std::vector<std::string>
ChatServer::splitString(const std::string& text) {
    std::istringstream iss(text);
    std::vector<std::string> tokens;
    std::string temp;

    while (iss >> std::quoted(temp)) {
        tokens.push_back(temp);
    }

    return tokens;
}

// /createroom --name ROOM_NAME --game ROOM_GAME
std::string
ChatServer::createRoom(const Message& message) {
    // Check arguments
    auto args = splitString(message.text);
    std::stringstream msgForUser;
    if ((args.size() != 5) || (args[1] != "--name") || (args[3] != "--game")) {
        msgForUser << "Command " << std::quoted("/createroom", '\'') << " has wrong syntax.\n";
        return msgForUser.str();
    }

    // Check if the User is already in a Room
    UserData user = connectionUserMap.at(message.connection);
    Room* roomPtr = user.room;
    if (roomPtr) {
        return "You must leave your current room before joining a new one\n";
    }

    constexpr int codeLength = 6;
    RoomId roomId = roomsGenerated;
    JoinCode joinCode{joinCodeGen.makeJoinCode(codeLength)};
    std::string name = args[2];
    std::string game = args[4];
    Room room{roomId, joinCode, name, game};
    rooms.push_back(room);
    messagesForRooms.emplace(roomId, "");
    roomsGenerated++;

    msgForUser << "Created room " << std::quoted(args[2]) << " playing game "
               << std::quoted(args[4]) << ". Join code is " << joinCode << "\n";
    return msgForUser.str();
}

// /joinroom JOIN_CODE
std::string
ChatServer::joinRoom(const Message& message) {
    // Check arguments
    auto args = splitString(message.text);
    std::stringstream msgForUser;
    if ((args.size() != 2) || args[1].empty()) {
        msgForUser << "Command " << std::quoted("/joinroom", '\'') << " has wrong syntax.\n";
        return msgForUser.str();
    }

    // Check if the User is already in a Room
    UserData& user = connectionUserMap.at(message.connection);
    Room* roomPtr = user.room;
    if (roomPtr) {
        return "You must leave your current room before joining a new one\n";
    }

    // Check if the join code is valid
    JoinCode joinCode{args[1]};
    auto roomIterator = std::find_if(std::begin(rooms), std::end(rooms), Room::FindByJoinCode(joinCode));
    if (roomIterator == std::end(rooms)) {
        msgForUser << "Could not find a room with join code " << joinCode << "\n";
        return msgForUser.str();
    }

    Room& room = *roomIterator;
    user.room = &room;
    room.addConnection(message.connection);

    msgForUser << "Joined room " << std::quoted(room.getName()) << " playing game "
               << std::quoted(room.getGame()) << "\n";
    return msgForUser.str();
}

// /leaveroom
std::string
ChatServer::leaveRoom(const Message& message) {
    // Check if the User is not in a Room
    UserData& user = connectionUserMap.at(message.connection);
    Room* roomPtr = user.room;
    if (!roomPtr) {
        return "Cannot leave room; you are not in a room\n";
    }

    std::string roomName = roomPtr->getName();
    user.room = nullptr;
    roomPtr->removeConnection(message.connection);

    std::stringstream msgForUser;
    msgForUser << "Left room " << std::quoted(roomName) << "\n";
    return msgForUser.str();
}

CommandResult
ChatServer::handleCommand(const Message& message) {
    CommandEffect status = CommandEffect::NOTHING;
    std::ostringstream msgForUser;

    if (message.text == "/quit" || message.text == "/exit") {
        msgForUser << "Disconnecting from the server...";
        status = CommandEffect::DISCONNECT;
    } else if (message.text == "/shutdown") {
        msgForUser << "Shutting the server down...";
        std::cout << "Shutting down.\n";
        status = CommandEffect::SHUTDOWN;
    } else if (message.text.rfind("/createroom", 0) == 0) {
        auto result = createRoom(message);
        msgForUser << result;
    } else if (message.text.rfind("/joinroom", 0) == 0) {
        auto result = joinRoom(message);
        msgForUser << result;
    } else if (message.text == "/leaveroom") {
        auto result = leaveRoom(message);
        msgForUser << result;
    } else {
        msgForUser << "Command " << std::quoted(message.text, '\'') << " is not recognized.\n";
    }

    return {status, msgForUser.str()};
}

bool
ChatServer::processMessages(const std::deque<Message>& incoming) {
    bool quit = false;
    for (const auto& message : incoming) {
        if (message.text.rfind("/", 0) == 0) {
            printableEvent = true;
            const auto [status, commandMsg] = handleCommand(message);
            sendUserServerMessage(message, commandMsg);
            switch (status) {
                case CommandEffect::DISCONNECT:
                    server.disconnect(message.connection);
                    break;
                case CommandEffect::SHUTDOWN:
                    quit = true;
                    break;
                default:
                    break;
            }
        } else {
            Room* room = connectionUserMap.at(message.connection).room;
            if (room) {
                messagesForRooms.at(room->getId()) << message.connection.id << "> " << message.text << "\n";
            } else {
                messagesForNullRoom << message.connection.id << "> " << message.text << "\n";
            }
        }
    }
    return quit;
}

void
ChatServer::sendUserServerMessage(Message message, const std::string& log) {
    UserData& user = connectionUserMap.at(message.connection);
    user.messagesFromServer.push_back(log);
}

std::deque<Message>
ChatServer::buildOutgoingNullRoom() {
    std::deque<Message> outgoing;
    for (const auto& [conn, data] : connectionUserMap) {
        Room* room = connectionUserMap.at(conn).room;
        if (!room) {
            outgoing.push_back({conn, messagesForNullRoom.str()});
        }
    }
    resetOStringStream(messagesForNullRoom);
    return outgoing;
}

std::deque<Message>
ChatServer::buildOutgoingPrivateServerMsg() {
    std::deque<Message> outgoing;
    for (auto& [conn, data] : connectionUserMap) {
        for (const auto& m : data.messagesFromServer) {
            outgoing.push_back({conn, m});
        }
        data.messagesFromServer.clear();
    }
    return outgoing;
}

std::deque<Message>
ChatServer::buildOutgoingRooms() {
    std::deque<Message> outgoing;
    for (auto& i : messagesForRooms) {
        RoomId roomId = i.first;
        auto roomIterator = std::find_if(std::begin(rooms), std::end(rooms), Room::FindById(roomId));
        if (roomIterator != std::end(rooms)) {
            Room& room = *roomIterator;
            auto roomConnections = room.getConnections();
            for (const auto& c : roomConnections) {
                outgoing.push_back({c, i.second.str()});     
            }
        }
        resetOStringStream(i.second);
    }
    
    return outgoing;
}

void ChatServer::resetOStringStream(std::ostringstream& ss) {
    ss.str({});
    ss.clear();
}

void
ChatServer::printUsersAndRooms(bool alwaysPrint) {
    if (!alwaysPrint && !printableEvent) {
        return;
    }
    
    std::cout << "\n";
    std::cout << timeString();
    std::cout << "USERS "
              << "(count=" << connectionUserMap.size() << ")"
              << ": {\n";
    for (const auto& [conn, data] : connectionUserMap) {
        std::cout << "  " << conn.id << " " << (data.room ? data.room->getJoinCode().code : "") << "\n";
    }
    std::cout << "}\n";

    std::cout << "ROOMS "
              << "(count=" << rooms.size() << ")"
              << ": {\n";
    for (const auto& i : rooms) {
        i.printAll();
    }
    std::cout << "}\n";

    printableEvent = false;
}

bool
ChatServer::update() {
    bool errorWhileUpdating = false;
    try {
        server.update();
    } catch (std::exception& e) {
        std::cerr << "Exception from Server update:\n"
                  << " " << e.what() << "\n\n";
        errorWhileUpdating = true;
    }

    const auto incoming = server.receive();
    const auto shouldQuit = processMessages(incoming);
    const auto outgoingForNullRoom = buildOutgoingNullRoom();
    server.send(outgoingForNullRoom);
    const auto outgoingFromServer = buildOutgoingPrivateServerMsg();
    server.send(outgoingFromServer);
    const auto outgoingForRooms = buildOutgoingRooms();
    server.send(outgoingForRooms);
    if (shouldQuit || errorWhileUpdating) {
        return true;
    }

    printUsersAndRooms(true);

    return false;
}

std::string
ChatServer::getHTTPMessage(const char* htmlLocation) {
    if (access(htmlLocation, R_OK) != -1) {
        std::ifstream infile{htmlLocation};
        return std::string{std::istreambuf_iterator<char>(infile),
                           std::istreambuf_iterator<char>()};
    }

    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
}

std::string
ChatServer::timeString() {
    std::ostringstream timeString;
    auto timeNow = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(timeNow);
    timeString << std::ctime(&t);
    return timeString.str();
}
