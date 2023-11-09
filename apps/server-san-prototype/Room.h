#pragma once

#include "ServerManager.h"
#include <vector>
#include <limits>

using namespace networking;

// namespace std {
//   template <>
//   struct hash<Connection> {
//     size_t
//     operator()(Connection c) const {
//       return std::hash<decltype(c.id)>{}(c.id);
//     }
//   };
// }
class ServerManager;
namespace ChatRoom
{
    struct RoomParams
    {
        Server &server;
        const Connection &admin_connection;
        size_t id;
        ServerManager &serverManager;
        std::unordered_map<Connection, size_t> &ConnectionRoomMap;
    };

    class Room
    {

    public:
        Room(RoomParams Params);
        void addConnection(const Connection &connection);
        void removeConnection(const Connection &connection);
        void moveConnectionMain(const Connection &connection);
        void addMessage(const Message &message);
        std::string getMessage();
        std::vector<Connection> getConnections();

    private:
        Server &server;
        ServerManager &serverManager;
        const Connection &admin; //no importance yet
        size_t roomId;
        std::vector<Connection> connections_;
        std::unordered_map<Connection, size_t> &connectionRoomMap;
        std::deque<Message> room_messages;
    };
    Room::Room(RoomParams Params)
        : server(Params.server),admin(Params.admin_connection), roomId(Params.id),serverManager(Params.serverManager),connectionRoomMap(Params.ConnectionRoomMap)
    {
        connections_.push_back(admin);
    }

    void Room::addConnection(const Connection &connection)
    {
        connections_.push_back(connection);
        connectionRoomMap[connection] = roomId;
    }

   

    //remove the connection for the list of connection local to this room and move the connection to the global room
    void Room::removeConnection(const Connection &connection)
    {   
        auto eraseBegin = std::remove(std::begin(connections_), std::end(connections_), connection);
        connections_.erase(eraseBegin, std::end(connections_));
        
        // serverManager.moveConnectionMain(connection); temp fix below to move connection to global room
        connectionRoomMap[connection] = std::numeric_limits<size_t>::max();
    }

    void Room::addMessage(const Message &message)
    {   

        if(message.text=="exit room"){

            removeConnection(message.connection);

            Message exitMessage{message.connection, "left room " + std::to_string(roomId) + " moved to Global Room\n"};
            server.sendPrivateMsg(exitMessage);
            return;
        }

        room_messages.push_back(message);
    }


    //this is being called by server every time it refreshes, kind of like emptying the buffer of messages in the room
    std::string Room::getMessage()
    {
        std::ostringstream result;

        if (room_messages.size() == 0)
        {
            return "";
        }

        while (!room_messages.empty())
        {
            auto message = room_messages.front();
            room_messages.pop_front();
            result << message.connection.id << "> " << message.text << "\n";
        }

        this->room_messages.clear();
        return result.str();
    }

    std::vector<Connection> Room::getConnections()
    {
        return connections_;
    }
};

