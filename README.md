# Social Gaming - Brawndo

This repository contains Team Brawndo's source code for CMPT 373's term project named **Social Gaming Platform**.

## Installation Steps

This project requires:

- C++17 or newer
- CMake >= 3.14

This project also has the dependencies included in the source code:

- GoogleTest v1.14.0

## Steps to run

Running cmake in spereate directory, should build the server and the nclient ncurses  

in the bin directory you should find 
.
├── client-ncurses
├── server
└── webchat.html

### run server 
ex webchat.html copied to bin dir on build
./server 4002 webchat.html 

### run client 

./client-ncurses localhost 4002


### supported client cmds (error handling not implemented)

#### Main menu (global room)
- join #  : join followed by number will validate id 
- create : will create room and display id to join 
- default cmds from server example still valid
#### Room menu (sub room created on create)
- exit room : any user may exit room
## current state
- filtering incoming messages into buckets, passing buckets to each room to process messages related to that room
- global room and one seperate room, messages are seperated clients in seperate room and global room see different messages 

## current issues
- build issue when sepereating implementation to different classes/files , took shortcuts just to build the server executable, however it needs to be cleaned up
