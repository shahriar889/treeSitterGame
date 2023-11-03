#ifndef SERVER_MODEL_USER_H
#define SERVER_MODEL_USER_H

#include "../../networking/include/Server.h"
#include "Room.h"

#include <vector>
#include <string>
#include <iostream>

using networking::Server;
using networking::Connection;
using networking::Message;

namespace server_model {


class Room;

class User {
private:
  Connection connection;
  Room* room;
  std::vector<std::string> messagesFromServer;

public:
  User(Connection connection, Room* room) : connection{connection}, room{room}
  {}
  ~User();
  
  Connection getConnection() const;

  Room* getRoom() const;
  void setRoom(Room* room);

  void addMessageFromServer(const std::string& log);
  std::vector<std::string> getMessagesFromServer() const;
  void clearMessagesFromServer();

  friend std::ostream& operator<<(std::ostream &os, const User &u);

  struct FindByConnection {
    FindByConnection(const Connection& lhs) : lhs(lhs) {}
    bool operator()(const User& rhs) const {return lhs == rhs.getConnection();}  
  private:
    const Connection& lhs;
  };
};


} // namespace server_model

#endif