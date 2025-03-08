#include "../include/Bomb.hpp"
#include <vector>

namespace navigation {
    double getDistance(MazeSquare *start, MazeSquare *end) {
        return std::sqrt(std::pow(end->i - start->i, 2) + std::pow(end->j - start->j, 2));
    }

    MazeSquare *findClosestBomb(MazeSquare *start, Bounds bounds) {
        bool init = false;
        std::pair<MazeSquare *, double> closestBomb = std::make_pair(nullptr, 0);
        for (uint8_t i = bounds.first.first; i < bounds.second.first; i++) {
            for (uint8_t j = bounds.first.second; j < bounds.second.second; j++) {
                auto square = gladiator->maze->getSquare(i, j);
                if (square->coin.value == 0) {
                    continue;
                }
                auto distance = getDistance(start, square);
                if (distance < closestBomb.second || !init) {
                    closestBomb = std::make_pair(square, distance);
                    init = true;
                }
            }
        }
        return closestBomb.first;
    }
}
