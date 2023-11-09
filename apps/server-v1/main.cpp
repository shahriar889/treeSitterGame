
#include <iostream>
#include "ServerManager.h"

int main(){
    ServerManager serverManager{};
    serverManager.ping();
    std::cout << "Hello World" << std::endl;
    return 0;
}