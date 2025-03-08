#pragma once

#include "gladiator.h"

extern Gladiator *gladiator;

using Bounds = std::pair<std::pair<uint8_t, uint8_t>, std::pair<uint8_t, uint8_t>>;

namespace navigation {
    MazeSquare *findClosestBomb(MazeSquare *start, Bounds bounds);
    MazeSquare *findClosestBombPath(MazeSquare *start, Bounds bounds);
}
