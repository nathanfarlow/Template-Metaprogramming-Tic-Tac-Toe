#include "tictactoe.hpp"

#include <array>

#define abs(a) (a >= 0 ? a : -1 * a)

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

Evaluation EvaluateBoard(const std::string &board_state) {
    return Evaluation::Xwins;
}

// Put other method definitions here