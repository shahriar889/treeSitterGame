#ifndef SERVER_MODEL_ROOM_H
#define SERVER_MODEL_ROOM_H

#include "../../networking/include/Server.h"
#include "User.h"
#include "JoinCode.h"

#include <vector>
#include <string>
#include <iostream>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.

using networking::Server;
using networking::Connection;
using networking::Message;


namespace server_model {


class User;

class Room {
private:
  std::vector<User*> players;
  boost::uuids::uuid uuid;
  JoinCode joinCode;
  std::string name;
  std::string game;

public:
  Room(boost::uuids::uuid uuid, JoinCode joinCode, std::string name, std::string game) 
    : uuid{uuid}, joinCode{joinCode}, name{name}, game{game}
  {
    std::cout << "Room() ran. Making new room " << uuid << "\n";
  }

  JoinCode getJoinCode() const;
  std::string getName() const;
  std::string getGame() const;
  boost::uuids::uuid getUuid() const;

  void addPlayer(User* user);
  void removePlayer(User* user);

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