#include "parser.h"

Parser::Parser(const std::string_view& path) {
    std::string sourceCode = getSourceCode(path);

    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};
    syntaxTree = parser.parseString(sourceCode);
}

Rule Parser::createRuleAbstraction() {
    ts::Node root = this->syntaxTree.getRootNode();
    ts::Cursor cursor = root.getCursor();

    //Use depth first search
}

//Helpers
std::string Parser::getSourceCode(const std::string_view& path) {
    std::filesystem::path projectDirectory = std::filesystem::current_path().parent_path();
    std::filesystem::path absolutePath = projectDirectory / path;
    std::ifstream input_file(absolutePath.string());

    if (!input_file.is_open()) {
        return "";
    }

    std::string sourceCode;
    std::string line;
    
    while (std::getline(input_file, line)) {
        sourceCode += line + '\n'; 
    }

    input_file.close(); 
    return sourceCode;
}
