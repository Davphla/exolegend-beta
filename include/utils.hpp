#pragma once

#include "gladiator.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

extern Gladiator *gladiator;

using coordinate_t = std::pair<int, int>;

static inline auto mazeToReal(coordinate_t coordinate) {
    auto squareSize = gladiator->maze->getSquareSize();
    return Position{
        coordinate.first * squareSize + (squareSize / 2),
        coordinate.second * squareSize + (squareSize / 2),
        0
    };
}
