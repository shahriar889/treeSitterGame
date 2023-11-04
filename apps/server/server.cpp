// /////////////////////////////////////////////////////////////////////////////
// //                         Single Threaded Networking
// //
// // This file is distributed under the MIT License. See the LICENSE file
// // for details.
// /////////////////////////////////////////////////////////////////////////////


#include "Server.h"


using networking::Connection;


namespace std {
  template <>
  struct hash<Connection> {
    size_t
    operator()(Connection c) const {
      return std::hash<decltype(c.id)>{}(c.id);
    }
  };
}


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