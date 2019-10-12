#include <iostream>

#include "tictactoe.hpp"

std::string evaluationNames[] = {
	"InvalidInput",
	"NoWinner",
	"Xwins",
	"Owins",
	"UnreachableState"
};

int main(int argc, char **argv) {

    if(argc <= 1)
        std::cout << "Please enter a tic tac toe state." << std::endl;
    else
        std::cout << evaluationNames[static_cast<int>(EvaluateBoard(argv[1]))] << std::endl;

    return 0;
}
