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
#include <limits>

// additons
#include <string_view>
#include <charconv>
#include "Room.h"

#include <cstdint>

// namespace std { this is what is being used to hash connection
//   template <>
//   struct hash<Connection> {
//     size_t
//     operator()(Connection c) const {
//       return std::hash<decltype(c.id)>{}(c.id);
//     }
//   };
// }


class ServerManager
{
public:
    ServerManager(unsigned short port, const char *htmlLocation);

    void run();

    size_t getGlobalRoomID() { return globalRoomID; }

    void moveConnectionMain(const Connection &connection);
  

private:
    size_t globalRoomID;
    std::vector<size_t> freeRoomIDs;   // pool of free room ids esstiatlly just a index of rooms that have been created but are no longer being used
    std::vector<ChatRoom::Room> rooms;

    std::unordered_map<Connection, size_t> ConnectionRoomMap; 
    std::vector<Connection> clients;

    Server server;

    void onConnect(Connection c);
    void onDisconnect(Connection c);
    void onMessage(Connection c, const std::string &message);
    void createRoom(const Connection &connection);//connection to create room becomes admin for room
    void joinRoom(const Connection &connection, size_t roomID);


    //move this fucntion into tools for string processing
    std::vector<std::string> split(const std::string &str, const std::string &delim);
    //clean up routine if no connection in room remove room
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




ServerManager::ServerManager(unsigned short port, const char *htmlLocation) : server(
                                                                                  port, getHTTPMessage(htmlLocation), [&](Connection c)
                                                                                  { onConnect(c); },
                                                                                  [&](Connection c)
                                                                                  { onDisconnect(c); })
{

    globalRoomID=std::numeric_limits<size_t>::max();
}

//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<std::string> ServerManager::split(const std::string &str, const std::string &delim){
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do{
        pos = str.find(delim, prev);
        if(pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if(!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }while(pos < str.length() && prev < str.length());
    return tokens;
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
    ConnectionRoomMap[c] = std::numeric_limits<size_t>::max();
}

void ServerManager::onDisconnect(Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
    clients.erase(eraseBegin, std::end(clients));

    //clean up room data related to connection
    if(ConnectionRoomMap[c] != globalRoomID){
        size_t roomID = ConnectionRoomMap[c];
        rooms[roomID].removeConnection(c);
    }

    //clean up undordered map remove entry for connection 
   ConnectionRoomMap.erase(c);
    
}
void ServerManager::moveConnectionMain(const Connection &connection)
{
        ConnectionRoomMap[connection] = globalRoomID;
}

void ServerManager::processRoomMessages(const std::deque<Message> &incomming_room_messages)
{
    for (const auto &message : incomming_room_messages)
    {
        size_t roomID = ConnectionRoomMap[message.connection];
        rooms[roomID].addMessage(message);
    }
}

void ServerManager::joinRoom(const Connection &Connection,size_t roomID){

    //check if room id is valid, currently not cleaning up room so if id less then rooms size then room is valid
    if(roomID > rooms.size()){
        server.sendPrivateMsg({Connection,"Invalid Room ID" + std::to_string(roomID) +" \n"});
        return;
    }
    //add connection to room
    rooms[roomID].addConnection(Connection);
    //notify connection of room id
    server.sendPrivateMsg({Connection,"Joined Room " + std::to_string(roomID) + "\n"});
    //notify room of connection
}

void ServerManager::createRoom(const Connection &connection)
{


    //make this a get id method
    size_t id = rooms.size(); //last index
    if(freeRoomIDs.empty()){

        //develop this condition for rooms that were created but no longer being used , they should be cleaned up and their id resused 
    }
    
    
    ChatRoom::RoomParams params{server,connection, id, *this, ConnectionRoomMap};
    ChatRoom::Room room{params};
    
    //add this to room vector
    rooms.push_back(room);
    //make the connection admin for the room
    //add the index of the room to the connection room map
    ConnectionRoomMap[connection] = id;

    //notify the creator of the id of the room
    //server.sendPrivateMsg({connection, "Created Room with ID " + std::to_string(id) + "\n"});

    Message joinMessage{connection, "Created room with ID " + std::to_string(id) + " use join "+std::to_string(id)+" to join room\n"};
    server.sendPrivateMsg(joinMessage);
    
}

ServerManager::MessageResult ServerManager::processMessages(const std::deque<Message> &incoming)
{
    std::ostringstream result;//global room message

    std::deque<Message> roomMessages;
    std::deque<Message> mainRoomMessages;

    for (const auto &message : incoming)
    {
        if (ConnectionRoomMap[message.connection] != globalRoomID)
        {
            roomMessages.push_back(message);
        }
        else
        {
            mainRoomMessages.push_back(message);
        }
    }

    processRoomMessages(roomMessages);

    bool quit = false;
    for (const auto &message : mainRoomMessages)
    {
        if (message.text == "quit")
        {
            server.disconnect(message.connection);
        }
        else if (message.text == "shutdown") //currently any user can shutdown the server maybe add admin rights on startup for shutting server down
        {
            std::cout << "Shutting down.\n";
            quit = true;
        }
        else if (message.text.find("join") == 0) //create fucntion to parse secong argument to number 
        {   
            
            std::vector<std::string> args = split(message.text," ");
            if(args.size() != 2){
                server.sendPrivateMsg({message.connection,"Invalid Arguments\n"});
                continue;
            }

            try{
                size_t roomID = std::stoul(args[1]);
                joinRoom(message.connection,roomID);
            }
            catch(std::exception &e){
                server.sendPrivateMsg({message.connection,"Invalid Arguments\n"});
            }
            

           //joinRoom(message.connection, );
        }
        else if (message.text == "create")
        {
            //std::cout << "Creating room\n";
            ServerManager::createRoom(message.connection);
        }else{
           result << message.connection.id << "> " << message.text << "\n"; //broadcast message to global room
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


