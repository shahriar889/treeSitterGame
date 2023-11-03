#include "chatserver.h"

ChatServer::ChatServer(unsigned short port, std::string httpMessage,
                       JoinCodeGenerator joinCodeGen, UUIDGenerator uuidGenerator)
    : server{Server(port, httpMessage,
        [&] (Connection c) {connectUser(c);},
        [&] (Connection c) {disconnectUser(c);})} 
    , joinCodeGen{joinCodeGen}
    , uuidGenerator{uuidGenerator}
{}

void
ChatServer::connectUser(Connection c) {
    std::cout << timeString();
    std::cout << "New connection found: " << c.id << "\n";
    User user{c, nullptr};
    // Things between < > don't show up on the HTML webpage. Using CAPS instead
    std::string newUserMsg =
        "Welcome new user!\n"
        "Feel free to chat with others in this public room.\n"
        "If you want to create a private room, send \"/createroom --name ROOM_NAME --game ROOM_GAME\".\n"
        "If you want to join a private room, send \"/joinroom JOIN_CODE\".\n";
    user.addMessageFromServer(newUserMsg);
    users.push_back(user);
}

void
ChatServer::disconnectUser(Connection c) {
    std::cout << timeString();
    std::cout << "Trying to disconnect " << c.id << "\n";

    // Find the User from the Connection
    auto userFindIterator = std::find_if(std::begin(users), std::end(users), User::FindByConnection(c));
    if (userFindIterator == std::end(users)) {
        std::cout << "disconnectUser: find_if failed to find User from Connection " << c.id << "\n";
        return;
    }
    std::cout << "disconnectUser: found a user\n";

    // Get the User's room. Delete them from their room
    User& user = *userFindIterator;
    std::cout << "disconnectUser: User is " << user << "\n";
    Room* userRoomPointer = user.getRoom();
    std::cout << "User room is " << userRoomPointer << "\n";
    if (userRoomPointer) {
        Room& usersRoom = *userRoomPointer;
        std::cout << "disconnectUser: user's room is " << usersRoom << "\n";
        usersRoom.removePlayer(&user);
        std::cout << "disconnectUser: passed removePlayer\n";
    } else {
        std::cout << "disconnectUser: User has no room.\n";
    }

    // Find the User from connection again, but this is for removal instead
    auto userRemoveIterator = std::remove_if(std::begin(users), std::end(users), User::FindByConnection(c));
    if (userRemoveIterator == std::end(users)) {
        std::cout << "disconnectUser: remove_if failed to find User from Connection " << c.id << "\n";
        return;
    }
    std::cout << "User size is, before delete, " << users.size() << "\n";
    users.erase(userRemoveIterator, std::end(users));
    std::cout << "User size is, after delete, " << users.size() << "\n";

    std::cout << "Successfully disconnected " << c.id << "\n";
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
    auto userIterator = std::find_if(std::begin(users), std::end(users), User::FindByConnection(message.connection));
    if (userIterator == std::end(users)) {
        std::cout << "createRoom: Failed to find User based on connection\n";
        return "Failed to create the room\n";
    }
    User& user = *userIterator;
    Room* userRoomPointer = user.getRoom();
    if (userRoomPointer) {
        return "You must leave your current room before creating a new one\n";
    }

    constexpr int codeLength = 6;
    auto uuid = uuidGenerator.makeUUID();
    JoinCode joinCode{joinCodeGen.makeJoinCode(codeLength)};
    std::string name = args[2];
    std::string game = args[4];
    Room room{uuid, joinCode, name, game};
    rooms.push_back(room);

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
    auto userIterator = std::find_if(std::begin(users), std::end(users), User::FindByConnection(message.connection));
    if (userIterator == std::end(users)) {
        std::cout << "joinRoom: Failed to find User based on connection\n";
        return "Failed to leave the room\n";
    }
    User& user = *userIterator;
    Room* userRoomPointer = user.getRoom();
    if (userRoomPointer) {
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
    user.setRoom(&room);
    room.addPlayer(&user);

    msgForUser << "Joined room " << std::quoted(room.getName()) << " playing game "
               << std::quoted(room.getGame()) << "\n";
    return msgForUser.str();
}

// /leaveroom
std::string
ChatServer::leaveRoom(const Connection& c) {
    auto userIterator = std::find_if(std::begin(users), std::end(users), User::FindByConnection(c));
    if (userIterator == std::end(users)) {
        std::cout << "leaveRoom: Failed to find User based on connection\n";
        return "Failed to leave the room\n";
    }

    User& user = *userIterator;
    Room* userRoomPointer = user.getRoom();
    if (!userRoomPointer) {
        return "Cannot leave room; you are not in a room\n";
    }
    Room& usersRoom = *userRoomPointer;
    std::string roomName = usersRoom.getName();
    usersRoom.removePlayer(&user);
    user.setRoom(nullptr);

    std::stringstream msgForUser;
    msgForUser << "Left room " << std::quoted(roomName) << "\n";
    return msgForUser.str();
}

CommandStatus
ChatServer::handleCommand(const Message& message) {
    std::ostringstream msgForUser;

    if (message.text == "/quit" || message.text == "/exit") {
        return CommandStatus::DISCONNECT;
    } else if (message.text == "/shutdown") {
        std::cout << "Shutting down.\n";
        return CommandStatus::SHUTDOWN;
    } else if (message.text.rfind("/createroom", 0) == 0) {
        auto result = createRoom(message);
        msgForUser << result;
    } else if (message.text.rfind("/joinroom", 0) == 0) {
        auto result = joinRoom(message);
        msgForUser << result;
    } else if (message.text == "/leaveroom") {
        auto result = leaveRoom(message.connection);
        msgForUser << result;
    } else {
        msgForUser << "Command " << std::quoted(message.text, '\'') << " is not recognized.\n";
    }

    sendUserServerMessage(message, msgForUser.str());
    return CommandStatus::NOTHING;
}

MessageResult
ChatServer::processMessages(const std::deque<Message>& incoming) {
    std::ostringstream result;
    bool quit = false;
    for (const auto& message : incoming) {
        if (message.text.rfind("/", 0) == 0) {
            switch (handleCommand(message)) {
                case CommandStatus::DISCONNECT:
                    server.disconnect(message.connection);
                    break;
                case CommandStatus::SHUTDOWN:
                    quit = true;
                    break;
                default:
                    break;
            }
        } else {
            result << message.connection.id << "> " << message.text << "\n";
        }
    }
    return MessageResult{result.str(), quit};
}

void
ChatServer::sendUserServerMessage(Message message, const std::string& log) {
    auto it = std::find_if(std::begin(users), std::end(users), User::FindByConnection(message.connection));
    if (it != std::end(users)) {
        User& user = *it;
        user.addMessageFromServer(log);
    }
}

std::deque<Message>
ChatServer::buildOutgoing(const std::string& log) {
    std::deque<Message> outgoing;
    for (const auto& u : users) {
        outgoing.push_back({u.getConnection(), log});
    }
    return outgoing;
}

std::deque<Message>
ChatServer::buildOutgoingPrivateServerMsg() {
    std::deque<Message> outgoing;
    for (auto& u : users) {
        auto messages = u.getMessagesFromServer();
        if (!messages.empty()) {
            for (const auto& i : messages) {
                outgoing.push_back({u.getConnection(), i});
            }
            u.clearMessagesFromServer();
        }
    }
    return outgoing;
}

void
ChatServer::printUsersAndRooms() {
    std::cout << "\n";
    std::cout << timeString();
    std::cout << "USERS "
              << "(count=" << users.size() << ")"
              << ": {\n";
    for (const auto& i : users) {
        std::cout << "  " << i << "\n";
    }
    std::cout << "}\n";

    std::cout << "ROOMS "
              << "(count=" << rooms.size() << ")"
              << ": {\n";
    for (const auto& i : rooms) {
        i.printAll();
    }
    std::cout << "}\n";
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
    const auto [log, shouldQuit] = processMessages(incoming);
    const auto outgoing = buildOutgoing(log);
    server.send(outgoing);
    const auto outgoingFromServer = buildOutgoingPrivateServerMsg();
    server.send(outgoingFromServer);
    if (shouldQuit || errorWhileUpdating) {
        return true;
    }

    printUsersAndRooms();

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
