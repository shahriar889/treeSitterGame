#include <gtest/gtest.h>
#include "parser.h"

const std::string LOOPING_GAME = "games/looping.game";

// Demonstrate some basic assertions.
TEST(ParserTest, createRules)
{
    Parser parser{LOOPING_GAME};
}