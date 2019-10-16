#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tictactoe.hpp"

TEST_CASE("No winner is detected") {
    REQUIRE(EvaluateBoard("xxo......") == Evaluation::NoWinner);
}

TEST_CASE("No winner is detected on empty board") {
    REQUIRE(EvaluateBoard(".........") == Evaluation::NoWinner);
}

TEST_CASE("No winner is detected on full board") {
	REQUIRE(EvaluateBoard("xoxooxxxo") == Evaluation::NoWinner);
}

TEST_CASE("Too many of one player is an unreachable state") {
	REQUIRE(EvaluateBoard("ooooxx-a-") == Evaluation::UnreachableState);
}

TEST_CASE("Horizontal X wins are detected") {
	REQUIRE(EvaluateBoard("xxx.b.oo.") == Evaluation::Xwins);
	REQUIRE(EvaluateBoard("...xxxoo.") == Evaluation::Xwins);
	REQUIRE(EvaluateBoard("oo....xxx") == Evaluation::Xwins);
}

TEST_CASE("Vertical X wins are detected") {
	REQUIRE(EvaluateBoard("xcdx.ox.o") == Evaluation::Xwins);
	REQUIRE(EvaluateBoard(".x.oxo.x.") == Evaluation::Xwins);
	REQUIRE(EvaluateBoard("..xolx.ox") == Evaluation::Xwins);
}

TEST_CASE("Diagonal X wins are detected") {
	REQUIRE(EvaluateBoard("..Xox.X=o") == Evaluation::Xwins);
	REQUIRE(EvaluateBoard("X..ox.o.x") == Evaluation::Xwins);
}

TEST_CASE("Horizontal O wins are detected") {
	REQUIRE(EvaluateBoard("oooxx....") == Evaluation::Owins);
	REQUIRE(EvaluateBoard(".xxooozzy") == Evaluation::Owins);
	REQUIRE(EvaluateBoard("ab.xx.ooo") == Evaluation::Owins);
}

TEST_CASE("Vertical O wins are detected") {
	REQUIRE(EvaluateBoard("o..o.xo.x") == Evaluation::Owins);
	REQUIRE(EvaluateBoard(".o..o.xox") == Evaluation::Owins);
	REQUIRE(EvaluateBoard("..o..oxxo") == Evaluation::Owins);
}

TEST_CASE("Diagonal O wins are detected") {
	REQUIRE(EvaluateBoard("o..xo..xo") == Evaluation::Owins);
	REQUIRE(EvaluateBoard("..o.o.oxx") == Evaluation::Owins);
}

TEST_CASE("Empty board is invalid") {
	REQUIRE(EvaluateBoard("") == Evaluation::InvalidInput);
}

TEST_CASE("Too small of board is invalid") {
	REQUIRE(EvaluateBoard("xox") == Evaluation::InvalidInput);
}

TEST_CASE("Too large of board is invalid") {
	REQUIRE(EvaluateBoard("xoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxox") == Evaluation::InvalidInput);
}
