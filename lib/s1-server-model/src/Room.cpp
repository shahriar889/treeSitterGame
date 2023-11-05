#include "Room.h"

using networking::Server;
using networking::Connection;
using networking::Message;

namespace server_model {
  

JoinCode Room::getJoinCode() const {
  return joinCode;
}
std::string Room::getName() const {
  return name;
}
std::string Room::getGame() const {
  return game;
}
boost::uuids::uuid Room::getUuid() const {
  return uuid;
}

void Room::addConnection(Connection c) {
  connections.push_back(c);
}

void Room::removeConnection(Connection c) {
  auto connFinder = [c] (Connection other) -> bool {
    return c == other;
  };
  auto connIterator = std::remove_if(std::begin(connections), std::end(connections), connFinder);
  connections.erase(connIterator, std::end(connections));
}

void Room::printAll() const {
  std::cout << "  Room[uuid=" << uuid
    << ", numPlayers=" << connections.size()
    << ", joinCode=" << joinCode
    // << ", name=" << name
    // <<", game=" << game
    << "]\n" ;
  for (const auto &c : connections) {
    std::cout << "    " << c.id << "\n";
  }
}

std::ostream& operator<<(std::ostream &os, const Room &r) { 
    return os << "Room[uuid=" << r.uuid << "]";
}


} // namespace server_model
