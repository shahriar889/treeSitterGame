// /////////////////////////////////////////////////////////////////////////////
// //                         Single Threaded Networking
// //
// // This file is distributed under the MIT License. See the LICENSE file
// // for details.
// /////////////////////////////////////////////////////////////////////////////


#include "Server.h"

// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <unistd.h>
// #include <vector>


// //additons
// #include <string_view>
// #include <charconv>
// #include "Room.h"
// #include <unordered_map>
// #include <cstdint>

// using networking::Server;
using networking::Connection;
// using networking::Message;


namespace std {
  template <>
  struct hash<Connection> {
    size_t
    operator()(Connection c) const {
      return std::hash<decltype(c.id)>{}(c.id);
    }
  };
}

// //or which room is free based on vector
// //when shutdown add room index to free pool
// //if shutdown index empty then append to end of vector
// //create id pool for free rooms
// //8446744073709551615 64 bit system 
// size_t globalRoomID = 0;
// std::vector<size_t> activeRoomIDs; //pool of active room ids
// std::vector<size_t> freeRoomIDs; //pool of free room ids esstiatlly just a
// std::vector<Connection> clients;
// std::vector<Room> rooms;
// std::unordered_map<Connection, unsigned int> ConnectionRoomMap;

// void
// onConnect(Connection c) {
//   std::cout << "New connection found: " << c.id << "\n";
//   clients.push_back(c);
//   ConnectionRoomMap[c]=globalRoomID;
// }


// void
// onDisconnect(Connection c) {
//   std::cout << "Connection lost: " << c.id << "\n";
//   auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
//   clients.erase(eraseBegin, std::end(clients));
// }


// struct MessageResult {
//   std::string result;
//   bool shouldShutdown;
// };



// //assing them to each room
// void 
// processRoomMessages(const std::deque<Message>& incomming_room_messages){


//    for (const auto& message : incomming_room_messages){

//       size_t roomID = ConnectionRoomMap[message.connection]-1;
//       rooms[roomID].addMessage(message);

//    }


// }


// //rooms and server messages join and create room
// //need to be seperated 
// MessageResult
// processMessages(Server& server, const std::deque<Message>& incoming) {
//   std::ostringstream result;

//   //seperate meesages based on connection to room ( un ordered has map connection and room ? O(1) time complexity)
//   //dispatch bucket to appropriate room to process
//   //expect room to output bucket of messages
//   //dipatch buckets to clients

//   //filter messages for rooms if nothing for room then proceed 
//   std::deque<Message> roomMessages;
//   std::deque<Message> globalMessages;

//   for (const auto& message : incoming) {
//     if (ConnectionRoomMap[message.connection] != globalRoomID) {
//       roomMessages.push_back(message);
//     } else {
//       globalMessages.push_back(message);
//     }
//   }

//   processRoomMessages(roomMessages);

//   bool quit = false;
//   for (const auto& message : globalMessages) {
//     if (message.text == "quit") {
//       server.disconnect(message.connection);
//     } else if (message.text == "shutdown") {
//       std::cout << "Shutting down.\n";
//       quit = true;
//     } else if (message.text.find("join")==0) {   //join room also has number the string contains number
//       //join room
//       size_t id=1;
//       std::cout <<message.connection.id<< " joining room id "<<id<<"\n";

//       //need to add check for valid room
//       rooms[id-1].addConnection(message.connection);
//       ConnectionRoomMap[message.connection]=id;
//       //if valid room pass the room this client connection

//     } else if ( message.text == "create" ) {
//       std::cout << "Creating room\n";
//       //vector.length is the room id
//       size_t id=rooms.size()+1;
//       if(id==1){


//         Room room{message.connection,id};
//         rooms.push_back(room);
//         ConnectionRoomMap[message.connection]=id;
//       }else{

//         std::cout << "Creating more then one room not implemented\n";
//       }
      
//       //create room and pass the room this client connection in constructor 

//     }else {
//       result << message.connection.id << "> " << message.text << "\n";
      
//     } 
//   }
//   return MessageResult{result.str(), quit};
// }

// //all messages it recieved will ve sent to all clients
// //room stores list of clients for all room do this build outgoing for all rooms

// std::deque<Message>
// buildOutgoing(const std::string& log) {


//   std::deque<Message> outgoing;

//   for (auto client : clients) { 

//     if(ConnectionRoomMap[client] == globalRoomID){
//       outgoing.push_back({client, log});
//     }
    
//   }

//   //for each room dispatch the message to all clients in the room

//   return outgoing;
// }



// std::deque<Message>
// buildOutgoingRoom() {

//   std::deque<Message> outgoing;

//   std::cout<<rooms.size()<<" active rooms\n";

//   for (auto &room : rooms) { 

//     std::string log = room.getMessage();
//     if(log.empty()){
//       continue;
//     }

//     for (auto client : room.getConnections()) { 
//       outgoing.push_back({client, log});
//     }
    
//   }

//   return outgoing;
// }




// std::string
// getHTTPMessage(const char* htmlLocation) {
//   if (access(htmlLocation, R_OK ) != -1) {
//     std::ifstream infile{htmlLocation};
//     return std::string{std::istreambuf_iterator<char>(infile),
//                        std::istreambuf_iterator<char>()};

//   }

//   std::cerr << "Unable to open HTML index file:\n"
//             << htmlLocation << "\n";
//   std::exit(-1);
// }


// int
// main(int argc, char* argv[]) {
//   if (argc < 3) {
//     std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
//               << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
//     return 1;
//   }

//   const unsigned short port = std::stoi(argv[1]);
//   Server server{port, getHTTPMessage(argv[2]), onConnect, onDisconnect};

//   while (true) {
//     bool errorWhileUpdating = false;
//     try {
//       server.update();
//     } catch (std::exception& e) {
//       std::cerr << "Exception from Server update:\n"
//                 << " " << e.what() << "\n\n";
//       errorWhileUpdating = true;
//     }

//     const auto incoming = server.receive();
//     const auto [log, shouldQuit] = processMessages(server, incoming);
//     const auto outgoing = buildOutgoing(log);
//     const auto outgoingRoom = buildOutgoingRoom();

//     server.send(outgoing);
//     server.send(outgoingRoom);


//     if (shouldQuit || errorWhileUpdating) {
//       break;
//     }

//     sleep(1);
//   }

//   return 0;
// }

#include "ServerManager.h"


int
main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
              << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
    return 1;
  }

  const unsigned short port = std::stoi(argv[1]);
  ServerManager roomManager{port, argv[2]};
  roomManager.run();
  return 0;
}