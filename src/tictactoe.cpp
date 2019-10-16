#include "tictactoe.hpp"

#include <array>
#include <cmath>

#define abs(a) ((a) >= 0 ? (a) : -1 * (a))

//Take a to the power of b
template<size_t a, size_t b>
struct Pow {
    enum {
        value = a * Pow<a, b - 1>::value
    };
};

template<size_t a>
struct Pow<a, 0> {
    enum {
        value = 1
    };
};

constexpr size_t kBoardArea = kBoardSideLength * kBoardSideLength;
constexpr size_t kTableSize = Pow<3, kBoardArea>::value;

typedef std::array<Evaluation, kTableSize> LookupTable;

constexpr size_t kXDigit = 1;
constexpr size_t kODigit = 2;

//Generate the digit at the row and column given the ternary state
template<size_t state, size_t row, size_t col, size_t index = kBoardArea - 1>
struct CharHelper {
    enum {
        value = index == kBoardSideLength * row + col ? state % 3
                : CharHelper<state / 3, row, col, index - 1>::value
    };
};

template<size_t row, size_t col, size_t index>
struct CharHelper<0, row, col, index> {
    enum {
        value = 0
    };
};

//Count how many entries of each player
template<size_t state, size_t player, size_t index = 0>
struct PlayerCounter {
    enum {
        value = (CharHelper<state, index / kBoardSideLength, index % kBoardSideLength>::value == player ? 1 : 0)
                + PlayerCounter<state, player, index + 1>::value
    };
};

template<size_t state, size_t player>
struct PlayerCounter<state, player, kBoardArea> {
    enum {
        value = 0
    };
};

//Check if a player won down a certain row
template<size_t state, size_t player, size_t row, size_t col = 0>
struct CheckRow {
    enum {
        value = CharHelper<state, row, col>::value == player
                && CheckRow<state, player, row, col + 1>::value
    };
};

template<size_t state, size_t player, size_t row>
struct CheckRow<state, player, row, kBoardSideLength> {
    enum {
        value = true
    };
};

//Check if a player won down a certain column
template<size_t state, size_t player, size_t col, size_t row = 0>
struct CheckColumn {
    enum {
        value = CharHelper<state, row, col>::value == player
                && CheckColumn<state, player, col, row + 1>::value
    };
};

template<size_t state, size_t player, size_t col>
struct CheckColumn<state, player, col, kBoardSideLength> {
    enum {
        value = true
    };
};

//Check if a player won any row or column
template<size_t state, size_t player, size_t index = 0>
struct RowColChecker {
    enum {
        value = CheckRow<state, player, index>::value
                || CheckColumn<state, player, index>::value
                || RowColChecker<state, player, index + 1>::value
    };
};

template<size_t state, size_t player>
struct RowColChecker<state, player, kBoardSideLength> {
    enum {
        value = false
    };
};

//Check if a player won a diagonal
template<size_t state, size_t player, bool isRightDiag, size_t row = 0, size_t col = 0>
struct CheckDiagonal {
    enum {
        value = CharHelper<state, isRightDiag ? row : kBoardSideLength - row - 1, col>::value == player
                && CheckDiagonal<state, player, isRightDiag, row + 1, col + 1>::value
    };
};

template<size_t state, size_t player, bool isRightDiag>
struct CheckDiagonal<state, player, isRightDiag, kBoardSideLength, kBoardSideLength> {
    enum {
        value = true
    };
};

//Check if a player has won in any condition
template<size_t state, size_t player>
struct CheckWin {
    enum {
        value = CheckDiagonal<state, player, true>::value
                || CheckDiagonal<state, player, false>::value
                || RowColChecker<state, player>::value
    };
};

//Evaluate a state
template<size_t state>
struct BoardEvaluator {
    static constexpr Evaluation value =
            abs((PlayerCounter<state, kXDigit>::value - PlayerCounter<state, kODigit>::value)) > 1
            || CheckWin<state, kXDigit>::value && CheckWin<state, kODigit>::value ? Evaluation::UnreachableState
                : CheckWin<state, kXDigit>::value ? Evaluation::Xwins
                : CheckWin<state, kODigit>::value ? Evaluation::Owins
                : Evaluation::NoWinner;
};

//Generate the lookup table
template<size_t index = 0, Evaluation ...D>
struct TableGenerator : TableGenerator<index + 1, D..., BoardEvaluator<index>::value> {};

template<Evaluation ...D>
struct TableGenerator<kTableSize, D...> {
    static constexpr LookupTable table = {D...};
};

//Contains the evaluation of each table, indexed at the table's
//ternary equivalent.
constexpr LookupTable lookup_table = TableGenerator<>::table;

//Convert a board into its ternary equivalent
size_t Convert(const std::string &board) {
    size_t accumulator = 0;

    for (size_t i = 0; i < kBoardArea; i++) {
        size_t power = kBoardArea - i - 1;

        if (board[i] == 'x' || board[i] == 'X')
            accumulator += kXDigit * static_cast<size_t>(std::pow(3, power));
        else if (board[i] == 'o' || board[i] == 'O')
            accumulator += kODigit * static_cast<size_t>(std::pow(3, power));
    }

    return accumulator;
}

Evaluation EvaluateBoard(const std::string &board_state) {
    if (board_state.length() != kBoardArea)
        return Evaluation::InvalidInput;

    return lookup_table[Convert(board_state)];
}
