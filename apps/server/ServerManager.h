/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Server.h"
using networking::Connection;
using networking::Message;
using networking::Server;




#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

// additons
#include <string_view>
#include <charconv>
#include "Room.h"

#include <cstdint>






class ServerManager
{
public:
    ServerManager(unsigned short port, const char *htmlLocation);

    void run();

    static constexpr size_t getGlobalRoomID() { return 0; }

private:

    std::vector<size_t> activeRoomIDs; // pool of active room ids
    std::vector<size_t> freeRoomIDs;   // pool of free room ids esstiatlly just a index
    std::vector<Connection> clients;
    std::vector<ChatRoom::Room> rooms;
    std::unordered_map<Connection, unsigned int> ConnectionRoomMap;
    Server server;

    void onConnect(Connection c);
    void onDisconnect(Connection c);
    void onMessage(Connection c, const std::string &message);

    struct MessageResult
    {
        std::string result;
        bool shouldShutdown;
    };

    void processRoomMessages(const std::deque<Message> &incomming_room_messages);
    MessageResult processMessages(const std::deque<Message> &incoming);
    std::deque<Message> buildOutgoing(const std::string &log);
    std::deque<Message> buildOutgoingRoom();
    std::string getHTTPMessage(const char *htmlLocation);
};


const size_t globalRoomID = 0;

ServerManager::ServerManager(unsigned short port, const char *htmlLocation) : server(
                                                                                  port, getHTTPMessage(htmlLocation), [&](Connection c)
                                                                                  { onConnect(c); },
                                                                                  [&](Connection c)
                                                                                  { onDisconnect(c); })
{
   
}

void ServerManager::run()
{
    while (true)
    {
        bool errorWhileUpdating = false;
        try
        {
            server.update();
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception from Server update:\n"
                      << " " << e.what() << "\n\n";
            errorWhileUpdating = true;
        }

        const auto incoming = server.receive();
        const auto [log, shouldQuit] = processMessages(incoming);
        const auto outgoing = buildOutgoing(log);
        const auto outgoingRoom = buildOutgoingRoom();
        
        if (shouldQuit || errorWhileUpdating)
        {
            break;
        }

        server.send(outgoing);
        server.send(outgoingRoom);
        sleep(1);
    }
}

void ServerManager::onConnect(Connection c)
{
    std::cout << "New connection found: " << c.id << "\n";
    clients.push_back(c);
    ConnectionRoomMap[c] = globalRoomID;
}

void ServerManager::onDisconnect(Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
    clients.erase(eraseBegin, std::end(clients));
}


void ServerManager::processRoomMessages(const std::deque<Message> &incomming_room_messages)
{
    for (const auto &message : incomming_room_messages)
    {
        size_t roomID = ConnectionRoomMap[message.connection] - 1;
        rooms[roomID].addMessage(message);
    }
}

ServerManager::MessageResult ServerManager::processMessages(const std::deque<Message> &incoming)
{
    std::ostringstream result;

    std::deque<Message> roomMessages;
    std::deque<Message> globalMessages;

    for (const auto &message : incoming)
    {
        if (ConnectionRoomMap[message.connection] != globalRoomID)
        {
            roomMessages.push_back(message);
        }
        else
        {
            globalMessages.push_back(message);
        }
    }

    processRoomMessages(roomMessages);

    bool quit = false;
    for (const auto &message : globalMessages)
    {
        if (message.text == "quit")
        {
            server.disconnect(message.connection);
        }
        else if (message.text == "shutdown")
        {
            std::cout << "Shutting down.\n";
            quit = true;
        }
        else if (message.text.find("join") == 0)
        {
            size_t id = 1;
            Message joinMessage{message.connection, "joined room " + std::to_string(id)};
            server.sendPrivateMsg(joinMessage);
            rooms[id - 1].addConnection(message.connection);
            ConnectionRoomMap[message.connection] = id;
        }
        else if (message.text == "create")
        {
            std::cout << "Creating room\n";
            size_t id = rooms.size() + 1;
            if (id == 1)
            {   
                ChatRoom::RoomParams params{server,message.connection, id,ConnectionRoomMap};
                ChatRoom::Room room{params};
                rooms.push_back(room);
                ConnectionRoomMap[message.connection] = id;
                server.sendPrivateMsg({message.connection, "Created Room with" + std::to_string(id)+"\n"});
            }
            else
            {
                server.sendPrivateMsg({message.connection, "Creating more then one room not implemented\n"});
            }
        }
        else
        {
            result << message.connection.id << "> " << message.text << "\n";
        }
    }
    return MessageResult{result.str(), quit};
}

std::deque<Message> ServerManager::buildOutgoing(const std::string &log)
{
    std::deque<Message> outgoing;
    for (auto client : clients)
    {
        if (ConnectionRoomMap[client] == globalRoomID)
        {
            outgoing.push_back({client, log});
        }
    }
    return outgoing;
}

std::deque<Message> ServerManager::buildOutgoingRoom()
{
    std::deque<Message> outgoing;
    std::cout << rooms.size() << " active rooms\n";
    for (auto &room : rooms)
    {
        std::string log = room.getMessage();
        if (log.empty())
        {
            continue;
        }
        for (auto client : room.getConnections())
        {
            outgoing.push_back({client, log});
        }
    }
    return outgoing;
}

std::string ServerManager::getHTTPMessage(const char *htmlLocation)
{
    if (access(htmlLocation, R_OK) != -1)
    {
        std::ifstream infile{htmlLocation};
        return std::string{std::istreambuf_iterator<char>(infile),
                           std::istreambuf_iterator<char>()};
    }
    std::cerr << "Unable to open HTML index file:\n"
              << htmlLocation << "\n";
    std::exit(-1);
}


