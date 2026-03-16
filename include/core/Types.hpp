#pragma once

#include <array>

constexpr int BOARD_SIZE = 19;

enum class Cell
{
    Empty,
    Black,
    White
};

using BoardGrid = std::array<std::array<Cell, BOARD_SIZE>, BOARD_SIZE>;