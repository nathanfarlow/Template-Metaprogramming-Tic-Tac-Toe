#include "tictactoe.hpp"

#include <array>
#include <cmath>

#define abs(a) ((a) >= 0 ? (a) : -1 * (a))

//Take a to the power of b
template<size_t a, size_t b>
struct TemplatePow {
    enum {value = a * TemplatePow<a, b - 1>::value};
};

template<size_t a>
struct TemplatePow<a, 0> {
    enum {value = 1};
};

constexpr size_t BOARD_SIDE_LENGTH = 3;
constexpr size_t BOARD_AREA = BOARD_SIDE_LENGTH * BOARD_SIDE_LENGTH;
constexpr size_t TABLE_SIZE = TemplatePow<3, BOARD_AREA>::value;

typedef std::array<Evaluation, TABLE_SIZE> LookupTable;

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

//Count how many entries of each player
template<size_t state, size_t player, size_t index = 0>
struct PlayerCounter {
    enum {value = (CharHelper<state, index / BOARD_SIDE_LENGTH, index % BOARD_SIDE_LENGTH>::value == player ? 1 : 0)
                  + PlayerCounter<state, player, index + 1>::value};
};
template<size_t state, size_t player>
struct PlayerCounter<state, player, BOARD_AREA> {
    enum {value = 0};
};

//Check if a player won down a certain row
template<size_t state, size_t player, size_t row, size_t col = 0>
struct CheckRow {
    enum {value = CharHelper<state, row, col>::value == player
            && CheckRow<state, player, row, col + 1>::value};
};
template<size_t state, size_t player, size_t row>
struct CheckRow<state, player, row, BOARD_SIDE_LENGTH> {
    enum {value = true};
};

//Check if a player won down a certain column
template<size_t state, size_t player, size_t col, size_t row = 0>
struct CheckColumn {
    enum {value = CharHelper<state, row, col>::value == player
            && CheckColumn<state, player, col, row + 1>::value};
};
template<size_t state, size_t player, size_t col>
struct CheckColumn<state, player, col, BOARD_SIDE_LENGTH> {
    enum {value = true};
};

//Check if a player won any row or column
template<size_t state, size_t player, size_t index = 0>
struct RowColChecker {
    enum {value = CheckRow<state, player, index>::value
            || CheckColumn<state, player, index>::value
            || RowColChecker<state, player, index + 1>::value};
};
template<size_t state, size_t player>
struct RowColChecker<state, player, BOARD_SIDE_LENGTH> {
    enum {value = false};
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

//Check if a player has won in any condition
template<size_t state, size_t player>
struct CheckWin {
    enum {value = CheckDiagonal<state, player, true>::value
            || CheckDiagonal<state, player, false>::value
            || RowColChecker<state, player>::value};
};

//Evaluate a state
template<size_t state>
struct BoardEvaluator {
    static constexpr Evaluation value = abs((PlayerCounter<state, X_CHAR>::value - PlayerCounter<state, O_CHAR>::value)) > 1
                                         || (CheckWin<state, X_CHAR>::value && CheckWin<state, O_CHAR>::value) ? Evaluation::UnreachableState
                                                 : CheckWin<state, X_CHAR>::value ? Evaluation::Xwins
                                                 : CheckWin<state, O_CHAR>::value ? Evaluation::Owins
                                                 : Evaluation::NoWinner;
};

//Generate the lookup table
template<size_t index = 0, Evaluation ...D>
struct TableGenerator : TableGenerator<index + 1, D..., BoardEvaluator<index>::value> {};

template<Evaluation ...D>
struct TableGenerator<TABLE_SIZE, D...> {
    static constexpr LookupTable table = {D...};
};

//Contains the evaluation of each table, indexed at the table's
//ternary equivalent.
constexpr LookupTable table = TableGenerator<>::table;

//Convert a board into its ternary equivalent
size_t convert(const std::string &board) {
    size_t accumulator = 0;

    for(size_t i = 0; i < BOARD_AREA; i++) {
        size_t power = BOARD_AREA - i - 1;

        if(board[i] == 'x' || board[i] == 'X')
            accumulator += X_CHAR * static_cast<size_t>(std::pow(3, power));
        else if(board[i] == 'o' || board[i] == 'O')
            accumulator += O_CHAR * static_cast<size_t>(std::pow(3, power));
    }

    return accumulator;
}

Evaluation EvaluateBoard(const std::string &board_state) {
    if(board_state.length() != BOARD_AREA)
        return Evaluation::InvalidInput;

    return table[convert(board_state)];
}
