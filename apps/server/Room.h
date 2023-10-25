#pragma once

#include "Server.h"
#include <vector>


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
namespace ChatRoom
{
    struct RoomParams
    {
        Server &server;
        const Connection &admin_connection;
        size_t id;
        std::unordered_map<Connection, unsigned int> &ConnectionRoomMap;
    };

    class Room
    {

    public:
        Room(RoomParams Params);

        void addConnection(const Connection &connection);

        void removeConnection(const Connection &connection);

        void addMessage(const Message &message);

        std::string getMessage();

        std::vector<Connection> getConnections();

    private:
        Server &server;
        const Connection &admin;
        size_t roomId;
        std::vector<Connection> connections_;
        std::unordered_map<Connection, unsigned int> &connectionRoomMap;
        std::deque<Message> room_messages;
    };
    Room::Room(RoomParams Params)
        : server(Params.server),admin(Params.admin_connection), roomId(Params.id), connectionRoomMap(Params.ConnectionRoomMap)
    {
        connections_.push_back(admin);
    }

    void Room::addConnection(const Connection &connection)
    {
        connections_.push_back(connection);
        connectionRoomMap[connection] = roomId;
    }

    void Room::removeConnection(const Connection &connection)
    {
        auto eraseBegin = std::remove(std::begin(connections_), std::end(connections_), connection);
        connections_.erase(eraseBegin, std::end(connections_));
        connectionRoomMap[connection] = 0;
    }

    void Room::addMessage(const Message &message)
    {   

        if(message.text=="exit room"){

            removeConnection(message.connection);
            Message exitMessage{message.connection, "left room " + std::to_string(roomId)};
            server.sendPrivateMsg(exitMessage);
            return;
        }

        room_messages.push_back(message);
    }

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

