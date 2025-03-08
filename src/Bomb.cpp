#include "../include/Bomb.hpp"
#include "PathFinder.hpp"
#include <vector>

namespace navigation {
    double getDistance(MazeSquare *start, MazeSquare *end) {
        return std::sqrt(std::pow(end->i - start->i, 2) + std::pow(end->j - start->j, 2));
    }

    MazeSquare *findClosestBomb(MazeSquare *start, Bounds bounds) {
        std::pair<MazeSquare *, double> closestBomb = std::make_pair(nullptr, std::numeric_limits<double>::max());
        for (uint8_t i = bounds.first.first; i < bounds.second.first; i++) {
            for (uint8_t j = bounds.first.second; j < bounds.second.second; j++) {
                auto square = gladiator->maze->getSquare(i, j);
                if (square->coin.value == 0) {
                    continue;
                }
                auto distance = getDistance(start, square);
                if (distance < closestBomb.second) {
                    closestBomb = std::make_pair(square, distance);
                }
            }
        }
        return closestBomb.first;
    }

    MazeSquare *findClosestBombPath(MazeSquare *start, Bounds bounds) {
        std::pair<MazeSquare *, std::pair<uint8_t, double>> closestBomb = std::make_pair(nullptr, std::make_pair<uint8_t, double>(std::numeric_limits<uint8_t>::max(), std::numeric_limits<double>::max()));
        for (uint8_t i = bounds.first.first; i < bounds.second.first; i++) {
            for (uint8_t j = bounds.first.second; j < bounds.second.second; j++) {
                auto square = gladiator->maze->getSquare(i, j);
                if (square->coin.value == 0) {
                    continue;
                }

                auto distance = getDistance(start, square);
                if (distance > closestBomb.second.second) {
                    continue;
                }
                auto path = PathFinder::findPath(start, square);
                auto pathSize = path.size();
                if (pathSize < closestBomb.second.first) {
                    closestBomb = std::make_pair(square, std::make_pair(pathSize, distance));
                }
            }
        }
        return closestBomb.first;
    }
}
