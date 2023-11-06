#ifndef SERVER_MODEL_ROOM_H
#define SERVER_MODEL_ROOM_H

#include "../../networking/include/Server.h"
#include "JoinCode.h"

#include <vector>
#include <string>
#include <iostream>

using networking::Server;
using networking::Connection;
using networking::Message;

using RoomId = int;

namespace server_model {

class Room {
private:
  std::vector<Connection> connections;
  RoomId id;
  JoinCode joinCode;
  std::string name;
  std::string game;

public:
  Room(RoomId id, JoinCode joinCode, std::string name, std::string game) 
    : id{id}, joinCode{joinCode}, name{name}, game{game}
  {
    std::cout << "Room() ran. Making new room with id " << id << "\n";
  }

  std::vector<Connection> getConnections() const;
  JoinCode getJoinCode() const;
  std::string getName() const;
  std::string getGame() const;
  RoomId getId() const;

  void addConnection(Connection c);
  void removeConnection(Connection c);

  void printAll() const;

  friend std::ostream& operator<<(std::ostream &os, const Room &r);

  struct FindByJoinCode {
    FindByJoinCode(const JoinCode& lhs) : lhs(lhs) {}
    bool operator()(const Room& rhs) const {return lhs == rhs.joinCode;}  
  private:
    const JoinCode& lhs;
  };
};


} // namespace server_model

#endif