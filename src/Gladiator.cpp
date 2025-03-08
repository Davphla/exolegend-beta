#include "Gladiator.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <map>
#include <vector>
#include <math.h>

#define ADD_SCORE_IF_POSSESSED(square)                                        \
    count += (square != nullptr && square->possession);

SentienceGladiator::score_t
SentienceGladiator::getCaseScore(const MazeSquare &maze)
{
    score_t count = 0;

    ADD_SCORE_IF_POSSESSED(maze.northSquare)
    ADD_SCORE_IF_POSSESSED(maze.southSquare)
    ADD_SCORE_IF_POSSESSED(maze.westSquare)
    ADD_SCORE_IF_POSSESSED(maze.eastSquare)
    return count;
}

coordinate_t SentienceGladiator::findClosestBomb(MazeSquare &cur)
{
    coordinate_t coords = {cur.i, cur.j};
    coordinate_t closestBomb = {0, 0};// default value, to change
    float minDistance = std::numeric_limits<float>::max();

    for (auto [coordinate, metric]: metrics) {
        if (metric.no_bomb == 0) {
            continue;
        }
        coordinate_t distance = {coordinate.first - coords.first, coordinate.second - coords.second};
        int dist = ABS(distance.first) + ABS(distance.second);
        if (dist < minDistance) {
            minDistance = dist;
            closestBomb = coordinate;
        }
    }
    return closestBomb;
}

void SentienceGladiator::fillNeighborsMetrics(const MazeSquare &maze)
{
    const std::vector<MazeSquare *> neighbors = {
        maze.northSquare, maze.southSquare, maze.westSquare, maze.eastSquare};

    for (MazeSquare *neighbor : neighbors) {
        if (neighbor != nullptr) {
            coordinate_t coords = {neighbor->i, neighbor->j};
            square_metric_t &cur_metric = metrics[coords];
            if (cur_metric.is_visited)
                continue;
            checkSquare(*neighbor, cur_metric);
        }
    }
}

void SentienceGladiator::checkSquare(const MazeSquare &maze,
                                     square_metric_t &cur)
{
    gladiator->log("%d - %d", maze.i, maze.j);
    cur.score = getCaseScore(maze);
    cur.is_visited = true;
    cur.no_bomb = maze.coin.value;

    // recursive call to explore all square
    fillNeighborsMetrics(maze);
}

void SentienceGladiator::processMaze(const MazeSquare &maze)
{
    coordinate_t coords = {maze.i, maze.j};
    square_metric_t &cur_metric = metrics[coords];

    checkSquare(maze, cur_metric);
    //std::sort(metrics.begin(), metrics.end(), [](const square_metric_t &a, const square_metric_t &b) {
    //    return a.score > b.score;
    //});
}
