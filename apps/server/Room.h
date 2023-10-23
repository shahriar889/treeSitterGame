#include "Server.h"
#include <vector>


using namespace networking;



class Room {

public:

    Room(const Connection& connection,size_t id) : admin(connection), roomId(id),update(false) {

        connections_.push_back(connection);
    }
    // other member functions and variables
    void addConnection(const Connection& connection) {
        connections_.push_back(connection);
    }

    void addMessage(const Message& message) {

        this->update = true;

        std::cout << "Room " << roomId << " got message from " << message.connection.id << "\n";
        
        room_messages.push_back(message);
    }



    
    std::string
    getMessage(){

        //empty deque
        std::ostringstream result;

        if(!update){
            
            std::cout << "no update\n";
            return "";

        }else{
                
            std::cout << "update is true\n";
        }

        if(room_messages.size() == 0){

            std::cout << "Room " << roomId << " is empty\n";
            return "";

        }

        while(!room_messages.empty()){

            auto message = room_messages.front();
            room_messages.pop_front();

            result << message.connection.id << "> " << message.text << "\n";
        }
       this->room_messages.clear();
       
        // std::cout <<"Room message :" << result.str();
        return result.str();

    } 

    std::vector<Connection> getConnections() {
        return connections_;
    }

private:

    const Connection& admin;
    bool update;
    size_t roomId;
    std::vector<Connection> connections_;
   
    std::deque<Message> room_messages;  
};
