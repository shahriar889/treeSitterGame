#pragma once
#include <cpp-tree-sitter.h>
#include <iostream>
#include <string>
#include <fstream>
#include <tuple>
#include <sstream>
#include <assert.h>

namespace TM {
    class TreeManager {
        public:
            explicit TreeManager(const std::string& filePath) noexcept;
            ts::Node getRoot() noexcept;
            std::tuple<int, ts::Node> findNodeBySymbol(const ts::Node& node,const ts::Symbol& targetSymbol) noexcept;
            std::string getSourceRange(const ts::Node& node) noexcept;
            std::tuple<int, int> getNumberRange(const ts::Node& node) noexcept;
            
        private:
            ts::Tree syntaxTree;
            std::string sourceCode;
    };
}