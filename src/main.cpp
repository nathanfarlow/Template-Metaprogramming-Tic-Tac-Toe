#include "tictactoe.hpp"

#include <iostream>

std::string evaluationNames[] = {
	"InvalidInput",
	"NoWinner",
	"Xwins",
	"Owins",
	"UnreachableState"
};

int main(int argc, char **argv) {

    if(argc <= 1)
        std::cout << "Usage: ./tictactoe [board state]" << std::endl;
    else
        std::cout << evaluationNames[static_cast<int>(EvaluateBoard(argv[1]))] << std::endl;

    return 0;
}
