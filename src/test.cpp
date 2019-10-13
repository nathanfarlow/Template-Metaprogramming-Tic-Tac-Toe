#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tictactoe.hpp"

TEST_CASE("No winner is detected") {
    REQUIRE(EvaluateBoard("O...X.X..") == Evaluation::NoWinner);
    REQUIRE(EvaluateBoard("xxo......") == Evaluation::NoWinner);
    REQUIRE(EvaluateBoard(".........") == Evaluation::NoWinner);
    REQUIRE(EvaluateBoard("xoxooxxxo") == Evaluation::NoWinner);
}

TEST_CASE("Unreachable states are detected") {
	SECTION("Two winners") {
		REQUIRE(EvaluateBoard("oooxxxoxx") == Evaluation::UnreachableState);
	}
	SECTION("Two many of one player") {
		REQUIRE(EvaluateBoard("ooooxx-a-") == Evaluation::UnreachableState);
	}
}

TEST_CASE("X win is detected") {
	SECTION("Horizontal") {
		REQUIRE(EvaluateBoard("xxx.b.oo.") == Evaluation::Xwins);
		REQUIRE(EvaluateBoard("...xxxoo.") == Evaluation::Xwins);
		REQUIRE(EvaluateBoard("oo....xxx") == Evaluation::Xwins);
	}
	SECTION("Vertical") {
		REQUIRE(EvaluateBoard("xcdx.ox.o") == Evaluation::Xwins);
		REQUIRE(EvaluateBoard(".x.oxo.x.") == Evaluation::Xwins);
		REQUIRE(EvaluateBoard("..xolx.ox") == Evaluation::Xwins);
	}
	SECTION("Diagonal") {
		REQUIRE(EvaluateBoard("..Xox.X=o") == Evaluation::Xwins);
		REQUIRE(EvaluateBoard("X..ox.o.x") == Evaluation::Xwins);
	}
}

TEST_CASE("O win is detected") {
	SECTION("Horizontal") {
		REQUIRE(EvaluateBoard("oooxx....") == Evaluation::Owins);
		REQUIRE(EvaluateBoard(".xxooozzy") == Evaluation::Owins);
		REQUIRE(EvaluateBoard("ab.xx.ooo") == Evaluation::Owins);
	}
	SECTION("Vertical") {
		REQUIRE(EvaluateBoard("o..o.xo.x") == Evaluation::Owins);
		REQUIRE(EvaluateBoard(".o..o.xox") == Evaluation::Owins);
		REQUIRE(EvaluateBoard("..o..oxxo") == Evaluation::Owins);	
	}
	SECTION("Diagonal") {
		REQUIRE(EvaluateBoard("o..xo..xo") == Evaluation::Owins);
		REQUIRE(EvaluateBoard("..o.o.oxx") == Evaluation::Owins);
	}
}

TEST_CASE("Invalid states are detected") {
	REQUIRE(EvaluateBoard("") == Evaluation::InvalidInput);
	REQUIRE(EvaluateBoard("xox") == Evaluation::InvalidInput);
	REQUIRE(EvaluateBoard("xoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxox") == Evaluation::InvalidInput);
}
