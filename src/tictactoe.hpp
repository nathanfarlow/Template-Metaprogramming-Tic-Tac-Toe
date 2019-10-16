#pragma once

#include <string>

constexpr size_t kBoardSideLength = 3;

enum class Evaluation {
    InvalidInput,
    NoWinner,
    Xwins,
    Owins,
    UnreachableState
};

Evaluation EvaluateBoard(const std::string &board_state);
