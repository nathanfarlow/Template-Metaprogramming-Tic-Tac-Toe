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
		REQUIRE(EvaluateBoard("oooxxxoxx") == Evaluation::Unreachable);
	}
	SECTION("Two many of one player") {
		REQUIRE(EvaluateBoard("ooooxx-a-") == Evaluation::Unreachable);
	}
}

TEST_CASE("X win is detected") {
	SECTION("Horizontal") {
		REQUIRE(EvaluateBoard("xxx.b.oo.") == Evaluation::Xwin);
		REQUIRE(EvaluateBoard("...xxxoo.") == Evaluation::Xwin);
		REQUIRE(EvaluateBoard("oo....xxx") == Evaluation::Xwin);
	}
	SECTION("Vertical") {
		REQUIRE(EvaluateBoard("xcdx.ox.o") == Evaluation::Xwin);
		REQUIRE(EvaluateBoard(".x.oxo.x.") == Evaluation::Xwin);
		REQUIRE(EvaluateBoard("..xolx.ox") == Evaluation::Xwin);
	}
	SECTION("Diagonal") {
		REQUIRE(EvaluateBoard("..Xox.X=o") == Evaluation::Xwin);
		REQUIRE(EvaluateBoard("X..ox.o.x") == Evaluation::Xwin);
	}
}

TEST_CASE("O win is detected") {
	SECTION("Horizontal") {
		REQUIRE(EvaluateBoard("oooxx....") == Evaluation::Owin);
		REQUIRE(EvaluateBoard(".xxooozzy") == Evaluation::Owin);
		REQUIRE(EvaluateBoard("ab.xx.ooo") == Evaluation::Owin);
	}
	SECTION("Vertical") {
		REQUIRE(EvaluateBoard("o..o.xo.x") == Evaluation::Owin);
		REQUIRE(EvaluateBoard(".o..o.xox") == Evaluation::Owin);
		REQUIRE(EvaluateBoard("..o..oxxo") == Evaluation::Owin);	
	}
	SECTION("Diagonal") {
		REQUIRE(EvaluateBoard("o..xo..xo") == Evaluation::Owin);
		REQUIRE(EvaluateBoard("..o.o.oxx") == Evaluation::Owin);
	}
}

TEST_CASE("Invalid states are detected") {
	REQUIRE(EvaluateBoard("") == Evaluation::InvalidInput);
	REQUIRE(EvaluateBoard("xox") == Evaluation::InvalidInput);
	REQUIRE(EvaluateBoard("xoxoxoxoxoxoxoxoxoxoxooxoxoxoxoxox") == Evaluation::InvalidInput);
}
