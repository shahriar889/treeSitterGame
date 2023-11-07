// /////////////////////////////////////////////////////////////////////////////
// //                         Single Threaded Networking
// //
// // This file is distributed under the MIT License. See the LICENSE file
// // for details.
// /////////////////////////////////////////////////////////////////////////////


// #include "Server.h"
#include "serverManager.h"
// #include "Room.h"


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