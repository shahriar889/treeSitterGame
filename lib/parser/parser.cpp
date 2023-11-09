#include "parser.h"

Parser::Parser(const std::string_view& path) : sourceCode(getSourceCode(path)) {
    ts::Language language = tree_sitter_socialgaming();
    ts::Parser parser{language};
    this->syntaxTree = std::make_unique<ts::Tree>(parser.parseString(sourceCode));
}

RuleManager Parser::createRuleManager() {
    ts::Node root = syntaxTree->getRootNode();
    ts::Node rulesNode = root.getChildByFieldName("rules");
    std::vector<Translator::RulePointer> rules;
    dfs(rulesNode, rules);

    RuleManager ruleManager(std::move(rules));
    return ruleManager;
}

void Parser::dfs(ts::Node node, std::vector<Translator::RulePointer>& rules) {
    Translator translator = buildTreeSitterTranslator();
    auto numChildren = node.getNumNamedChildren();

    auto rule = translator.createOperation(std::string{node.getType()});
    //if nested, pass this vector instead
    std::vector<Translator::RulePointer> nestedRules;
    if (rule && rule->isNested()) {
        for (int i = 0; i < numChildren; i++) {
             dfs(node.getNamedChild(i), nestedRules);
        }
    }
    else {
        for (int i = 0; i < numChildren; i++) {
            dfs(node.getNamedChild(i), rules);
        }
    }

    if (rule) {
        if (rule->isNested()) {
            dynamic_cast<NestedRule*>(rule.get())->setRules(std::move(nestedRules));
        }
        rules.emplace_back(std::move(rule));
    }
}


//Helpers
std::string Parser::getSourceCode(const std::string_view& path) {
    std::filesystem::path projectDirectory = std::filesystem::current_path();
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
