#include "Gladiator.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <map>
#include <math.h>
#include <vector>

SentienceGladiator::score_t
SentienceGladiator::getCaseScore(const MazeSquare &maze)
{
    score_t count = 0;
#define ADD_SCORE_IF_NOT_POSSESSED(square)                                    \
    (square != nullptr && square->possession == 0)

    count += ADD_SCORE_IF_NOT_POSSESSED(maze.northSquare);
    count += ADD_SCORE_IF_NOT_POSSESSED(maze.southSquare);
    count += ADD_SCORE_IF_NOT_POSSESSED(maze.westSquare);
    count += ADD_SCORE_IF_NOT_POSSESSED(maze.eastSquare);
    return count;
}

bool check_shrink(std::pair<uint, uint> coord, uint shrink, uint map_size)
{
    printf("Checking shrink for coordinates (%u, %u) with shrink value %u and "
           "map size %u\n",
           coord.first, coord.second, shrink, map_size);
    return (
        ((int) (coord.first - shrink) < 0 || coord.first + shrink >= map_size)
        || ((int) (coord.second - shrink) < 0
            || coord.second + shrink >= map_size));
}

coordinate_t SentienceGladiator::findClosestBomb(MazeSquare &cur)
{
    coordinate_t coords = {cur.i, cur.j};
    coordinate_t closestBomb = {1, 1};// default value, to change
    float minDistance = std::numeric_limits<float>::max();

    for (auto [coordinate, metric] : metrics) {
        if (metric.no_bomb == 0
            || check_shrink(coordinate, shrink_value, MAP_SIZE)) {
            continue;
        }
        coordinate_t distance = {coordinate.first - coords.first,
                                 coordinate.second - coords.second};
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
    cur.score = getCaseScore(maze);
    cur.is_visited = true;
    cur.no_bomb = maze.coin.value;
    cur.coords = {maze.i, maze.j};

    // recursive call to explore all square
    fillNeighborsMetrics(maze);
}

void SentienceGladiator::reset()
{
    metrics.clear();
}

void SentienceGladiator::calculateBestEntry(const MazeSquare &maze)
{
    std::vector<square_metric_t> metric_list;
    for (auto &[coordinate, entry] : metrics) {
        if (check_shrink(coordinate, shrink_value, MAP_SIZE)) {
            continue;
        }
        coordinate_t distance = {coordinate.first - maze.i,
                                 coordinate.second - maze.j};
        entry.final_score = entry.score
            / (1.0
               + std::sqrt(distance.first * distance.first
                           + distance.second * distance.second));
        metric_list.push_back(entry);
    }

    std::sort(metric_list.begin(), metric_list.end(),
              [](const square_metric_t &a, const square_metric_t &b) {
                  return a.final_score > b.final_score;
              });
#if DEBUG
    for (square_metric_t entry : metric_list) {
        std::cout << entry.final_score << " ";
    }
    std::cout << std::endl;
#endif
    for (size_t i = 0; i < NB_ENTRY && i < metric_list.size(); ++i) {
        best_entries.push_back(metric_list[i]);
    }
}

void SentienceGladiator::processMaze(const MazeSquare &maze)
{
    coordinate_t coords = {maze.i, maze.j};
    square_metric_t &cur_metric = metrics[coords];

    reset();
    checkSquare(maze, cur_metric);
    if (gladiator->weapon->getBombCount() != 0) {
        calculateBestEntry(maze);
    }
    /*for (square_metric_t entry : metric_list) {
        std::cout << entry.final_score << " ";
    }
    std::cout << std::endl;*/
}
