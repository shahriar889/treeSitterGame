#pragma once

#include <string>
#include <vector>

class Node {
    public:
        Node(std::string, std::vector<Node>);
        void execute();
    private:
        std::string type;
        std::vector<Node> body;
};