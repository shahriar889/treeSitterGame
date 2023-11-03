#include "User.h"
#include <boost/uuid/uuid_io.hpp>

using networking::Server;
using networking::Connection;
using networking::Message;

namespace server_model {


User::~User() {
  // std::cout << "User " << connection.id << " is destroyed\n";
}

Connection User::getConnection() const {
  return connection;
}

Room* User::getRoom() const {
  return room;
}

void User::setRoom(Room* room) {
  this->room = room;
}

void User::addMessageFromServer(const std::string& log) {
  messagesFromServer.push_back(log);
}

std::vector<std::string> User::getMessagesFromServer() const {
  return messagesFromServer;
}

void User::clearMessagesFromServer() {
  messagesFromServer.clear();
}

std::ostream& operator<<(std::ostream &os, const User &u) { 
    return os
      << "User[connection=" << u.connection.id
      << ", room=" << (u.room ? boost::uuids::to_string(u.room->getUuid()) : "null")
      << "]";
}

  
} // namespace server_model
