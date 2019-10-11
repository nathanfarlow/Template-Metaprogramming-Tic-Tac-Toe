#pragma once

#include <string>

enum class Evaluation {
    InvalidInput,
    NoWinner,
    Xwins,
    Owins,
    UnreachableState
};

Evaluation EvaluateBoard(const std::string &board_state);

// Put other methods, enums, classes, etc. declarations here

