#include "treeManager.h"
#include "gtest/gtest.h"
#include <string>
#include <filesystem>

TEST(TreeManagerTest, testWithRockPaperScissors){
  // Get the project directory path
    std::filesystem::path projectDirectory = std::filesystem::current_path();

    // Define the relative path to your file
    std::string relativePath = "games/rock-paper-scissors.game";

    // Construct the absolute path by concatenating the project directory and the relative path
    std::filesystem::path absolutePath = projectDirectory / relativePath;
    TM::TreeManager treeManager(absolutePath);
    ts::Node root = treeManager.getRoot();
    EXPECT_EQ(root.getSymbol(), ts::Symbol(90));
    std::tuple<int, ts::Node> node = treeManager.findNodeBySymbol(root, ts::Symbol(94));
    EXPECT_EQ(std::get<0>(node), 1);
    EXPECT_EQ(std::get<1>(node).getSymbol(), ts::Symbol(94));
    node = treeManager.findNodeBySymbol(root, ts::Symbol(84));
    EXPECT_EQ(std::get<0>(node), 1);
    EXPECT_EQ(std::get<1>(node).getSymbol(), ts::Symbol(84));
    std::string sourceRange = treeManager.getSourceRange(std::get<1>(node));
    EXPECT_EQ(sourceRange, "Rock, Paper, Scissors");
    node = treeManager.findNodeBySymbol(root, ts::Symbol(124));
    EXPECT_EQ(std::get<0>(node), 1);
    EXPECT_EQ(std::get<1>(node).getSymbol(), ts::Symbol(124));
    std::tuple<int, int> numberRange = treeManager.getNumberRange(std::get<1>(node));
    EXPECT_EQ(std::get<0>(numberRange), 2);
    EXPECT_EQ(std::get<1>(numberRange), 4);

}