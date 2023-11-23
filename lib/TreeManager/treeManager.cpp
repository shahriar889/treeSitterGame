#include "treeManager.h"
#include <fstream>
#include <iostream>
#include <sstream>

extern "C" {
    TSLanguage* tree_sitter_socialgaming();
}

TM::TreeManager::TreeManager(const std::string& filePath) noexcept : syntaxTree{nullptr}{
    std::ifstream file(filePath);
    std::string sourcecode;

    std::ifstream input_file(filePath);
    if (!input_file.is_open()) {
        std::cerr << "Error: Unable to open file\n";
    }

    std::string line;
    while (std::getline(input_file, line)) {
        sourcecode += line + '\n'; 
    }

    input_file.close();
    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};
    syntaxTree = parser.parseString(sourcecode);
    this->sourceCode = sourcecode;
}

ts::Node TM::TreeManager::getRoot() noexcept {
    return syntaxTree.getRootNode();
}

//Function looks for a node with the argument symbol, rooted from the given node
//If given symbol is not present function will return (-1, node)
//If found it will send (1,node)
//Since node dont have any default constructor we can send any default node, that is why I am returning an int as check
std::tuple<int, ts::Node> TM::TreeManager::findNodeBySymbol (const ts::Node& node, const ts::Symbol& targetSymbol) noexcept{
    // Check if the current node's symbol matches the target
    if (node.getSymbol() == targetSymbol) {
        std::tuple<int, ts::Node> temp(1,node); // Return the node if found
        return temp;
    }

    // Recursively search in the children of the current node
    for (uint32_t i = 0; i < node.getNumChildren(); i++) {
        std::tuple<int,ts::Node> child = findNodeBySymbol((node.getChild(i)), targetSymbol);

        // If the node with the target symbol is found in the child, return it
        if (std::get<0>(child) > 0) {
            return child;
        }
    }

    // If not found in the current node or its children, return nullptr
    std::tuple<int, ts::Node> temp2(-1,node);
    return temp2;
}

std::string TM::TreeManager::getSourceRange(const ts::Node& node) noexcept {
    std::string_view x = node.getSourceRange(sourceCode);
    std::string sourceRangeContent = std::string(x);
    if (sourceRangeContent.size() >= 2 && sourceRangeContent.front() == '"' && sourceRangeContent.back() == '"') {
        sourceRangeContent = sourceRangeContent.substr(1, sourceRangeContent.size() - 2);
    }
    return sourceRangeContent;
}

std::tuple<int, int> TM::TreeManager::getNumberRange(const ts::Node& node) noexcept {
    std::string sourceRangeContent = getSourceRange(node);
    std::istringstream iss(sourceRangeContent);
    char delimiter; // To store the comma and parentheses
    int num1, num2;

    // Read and discard the opening parenthesis
    iss >> delimiter;

    // Read the first number
    iss >> num1;

    // Read the comma
    iss >> delimiter;

    // Read the second number
    iss >> num2;

    // Read and discard the closing parenthesis
    iss >> delimiter;

    assert(!iss.fail());
    std::tuple<int, int> range(0,0); 
    if(num1 != num2){
        std::tuple<int, int> temp(num1,num2);
        range = temp;
    }
    return range;        
}

