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

void Room::addPlayer(User* user) {
  players.push_back(user);
}

void Room::removePlayer(User* user) {
  auto userFinder = [user] (User* u) -> bool {
    return (*u).getConnection() == (*user).getConnection();
  };
  auto userIterator = std::remove_if(std::begin(players), std::end(players), userFinder);
  players.erase(userIterator, std::end(players));
}

void Room::printAll() const {
  std::cout << "  Room[uuid=" << uuid
    << ", numPlayers=" << players.size()
    << ", joinCode=" << joinCode
    // << ", name=" << name
    // <<", game=" << game
    << "]\n" ;
  for (const auto &i : players) {
    std::cout << "    " << *i << "\n";
  }
}

std::ostream& operator<<(std::ostream &os, const Room &r) { 
    return os << "Room[uuid=" << r.uuid << "]";
}


} // namespace server_model
