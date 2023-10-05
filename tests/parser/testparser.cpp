#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>

#include <cpp-tree-sitter.h>

using namespace ts;

//this will print the tree from the node passed in as root
//will  not print the sibling nodes
//filtering the comments and printing the node type and node symbol
//some nodes have no symbol name and type is number
void print_node(Node root, int depth);


extern "C" {
TSLanguage* tree_sitter_socialgaming();
}

int main(int argc, char* argv[]) {

    if (argc < 2)  {
        std::cerr << "Error: No file path given\n" ;
        return 1;
    }

    std::string file_path = argv[1];
    std::string sourcecode;

    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
        std::cerr << "Error: Unable to open file\n";
        return 1;
    }

    std::string line;
    while (std::getline(input_file, line)) {
        sourcecode += line + '\n'; 
    }

    input_file.close();

    // Create a language and parser.
    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};

    // Parse the provided string into a syntax tree.
    ts::Tree tree = parser.parseString(sourcecode);

    // Get the root node of the syntax tree. 
    ts::Node root = tree.getRootNode();

    // Print the syntax tree as an S-expression.
    auto treestring = root.getSExpr();
    //printf("Syntax tree: %s\n", treestring.get());
    print_node(root,0);
    
    return 0;
}



void print_node(Node root, int depth) {

  if(root.getType()=="comment") return;
  std::cout << std::string(depth * 2, ' ') << root.getType() << " " << root.getSymbol() << std::endl;
  if (root.hasError()) {
    std::cout << " (error)";
  }

  for (uint32_t i = 0, n = root.getNumChildren(); i < n; i++) {
    Node child = root.getChild(i);
    print_node(child, depth + 1);
  }


}
