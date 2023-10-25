# Social Gaming - Brawndo

This repository contains CMPT 373 Team Brawndo's term project for **Social-Gaming**

## Installation Steps

Minimum requirements

- Minumum CMake 3+
- Minimum C++17

## Steps to run

Running cmake in spereate directory, should build the server and the nclient ncurses in the top level directory 

in the bin directory 

### run server 

./server 4002 ../../social-gaming/web-socket-networking/webchat.html 

### run client 

./client-ncurses localhost 4002


### supported client cmds (error handling not implemented)

#### Main menu (global room)
- join   : will join default room with id 1 (expects room 1 has been created)
- create : will create room with id 1 
#### Room menu (sub room created on create)
- exit room (non admin client will be moved back to global room)
## current state
- filtering incoming messages into buckets, passing buckets to each room to process messages related to that room
- global room and one seperate room, messages are seperated clients in seperate room and global room see different messages 
- .....details to elborate on in meeting
