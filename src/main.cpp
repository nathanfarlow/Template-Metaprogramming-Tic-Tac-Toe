#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tictactoe.hpp"

// See: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md
// For documentation on how to write tests with Catch2

TEST_CASE("Incomplete boards have no winner") {
    REQUIRE(EvaluateBoard("O...X.X..") == Evaluation::NoWinner);
}