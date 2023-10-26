#include "parser.h"

Parser::Parser(const std::string_view& path) {
    std::string sourceCode = getSourceCode(path);

    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};
    this->syntaxTree = std::make_unique<ts::Tree>(parser.parseString(sourceCode));
}

Rule Parser::createRuleAbstraction() {
    ts::Node root = syntaxTree->getRootNode();
    ts::Node rulesNode = root.getChildByFieldName("rules");
    //Use depth first search
    dfs(rulesNode);

    return Rule{};
}

void Parser::dfs(ts::Node node) {
    auto numChildren = node.getNumNamedChildren();

    std::cout << node.getType() << "\n";
    for (int i = 0; i < numChildren; i++) {
        dfs(node.getNamedChild(i));
    }
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
