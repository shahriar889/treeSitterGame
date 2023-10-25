#include "parser.h"

Parser::Parser(const std::string_view& path) {
    std::string sourceCode = getSourceCode(path);

    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};
    this->syntaxTree = std::make_unique<ts::Tree>(parser.parseString(sourceCode));
}

Rule Parser::createRuleAbstraction() {
    ts::Node root = syntaxTree->getRootNode();
    ts::Cursor cursor = root.getCursor();
    
    //Use depth first search
    dfs(cursor.getCurrentNode());

    return Rule{};
}

void Parser::dfs(ts::Node node) {
    ts::Cursor cursor = node.getCursor();

    do {
        auto node = cursor.getCurrentNode();
        //TODO: Perform some processing
        std::cout << node.getType() << "\n";        
        if (cursor.gotoFirstChild()) {
            dfs(cursor.getCurrentNode());
            auto temp = cursor.gotoParent();
        }

    } while (cursor.gotoNextSibling());
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
