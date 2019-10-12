#include "tictactoe.hpp"

#include <array>

#define abs(a) ((a) >= 0 ? (a) : -1 * (a))

template<size_t a, size_t b>
struct pow {
    enum {value = a * pow<a, b - 1>::value};
};

template<size_t a>
struct pow<a, 0> {
    enum {value = 1};
};

constexpr size_t BOARD_SIDE_LENGTH = 2;
constexpr size_t BOARD_AREA = BOARD_SIDE_LENGTH * BOARD_SIDE_LENGTH;
constexpr size_t TABLE_SIZE = pow<3, BOARD_AREA>::value;

typedef std::array<Evaluation, TABLE_SIZE> LookupTable;

constexpr size_t EMPTY_CHAR = 0;
constexpr size_t X_CHAR = 1;
constexpr size_t O_CHAR = 2;

//Generate the digit at the row and column given the ternary state
template<size_t state, size_t row, size_t col, size_t index = BOARD_AREA - 1>
struct CharHelper {
    enum {value = index == BOARD_SIDE_LENGTH * row + col ? state % 3
            : CharHelper<state / 3, row, col, index - 1>::value};
};
template<size_t row, size_t col, size_t index>
struct CharHelper<0, row, col, index> {
    enum {value = 0};
};

//Check if a player won down a certain row
template<size_t state, size_t row, size_t player, size_t col = 0>
struct CheckRow {
    enum {value = CharHelper<state, row, col>::value == player
            && CheckRow<state, row, player, col + 1>::value};
};
template<size_t state, size_t row, size_t player>
struct CheckRow<state, row, player, BOARD_SIDE_LENGTH> {
    enum {value = true};
};

//Check if a player won down a certain column
template<size_t state, size_t col, size_t player, size_t row = 0>
struct CheckColumn {
    enum {value = CharHelper<state, row, col>::value == player
            && CheckColumn<state, col, player, row + 1>::value};
};
template<size_t state, size_t col, size_t player>
struct CheckColumn<state, col, player, BOARD_SIDE_LENGTH> {
    enum {value = true};
};

//Check if a player won any row or column
template<size_t state, size_t player, size_t index = 0>
struct RowColChecker {
    enum {value = CheckRow<state, player, index>::value
            && CheckColumn<state, player, index>::value
            && RowColChecker<state, player, index + 1>::value};
};

template<size_t state, size_t player>
struct RowColChecker<state, player, BOARD_SIDE_LENGTH> {
    enum {value = true};
};

//Check if a player won a diagonal
template<size_t state, size_t player, bool isRightDiag, size_t row = 0, size_t col = 0>
struct CheckDiagonal {
    enum {value = CharHelper<state, isRightDiag ? row : BOARD_SIDE_LENGTH - row - 1, col>::value == player
                && CheckDiagonal<state, player, isRightDiag, row + 1, col + 1>::value};
};
template<size_t state, size_t player, bool isRightDiag>
struct CheckDiagonal<state, player, isRightDiag, BOARD_SIDE_LENGTH, BOARD_SIDE_LENGTH> {
    enum {value = true};
};

Evaluation EvaluateBoard(const std::string &board_state) {
    return Evaluation::Xwins;
}

// Put other method definitions here