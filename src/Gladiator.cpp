#include "Gladiator.hpp"
#include <algorithm>
#include <map>
#include <vector>


static score_t getCaseScore(const MazeSquare &maze)
{
    score_t count = 0;
#define ADD_SCORE_IF_POSSESSED(square)                                        \
    count += (square != nullptr && square->possession);

    ADD_SCORE_IF_POSSESSED(maze.northSquare)
    ADD_SCORE_IF_POSSESSED(maze.southSquare)
    ADD_SCORE_IF_POSSESSED(maze.westSquare)
    ADD_SCORE_IF_POSSESSED(maze.eastSquare)
    return count;
}

static void checkSquare(const MazeSquare &maze, square_metric_t &cur,
                        metrics_t &metrics)
{
    cur.score = getCaseScore(maze);

    // recursive call to explore all square
    fillNeighborsMetrics(maze, metrics);
}

static void fillNeighborsMetrics(const MazeSquare &maze, metrics_t &metrics)
{
    score_t current_square_score = getCaseScore(maze);
    const std::vector<MazeSquare *> neighbors = {
        maze.northSquare, maze.southSquare, maze.westSquare, maze.eastSquare};

    for (MazeSquare *neighbor : neighbors) {
        if (neighbor != nullptr) {
            coordinate_t coord = {neighbor->i, neighbor->j};
            square_metric_t &cur_metric = metrics[coord];
            if (cur_metric.score)
                continue;
            checkSquare(*neighbor, cur_metric, metrics);
        }
    }
}

void SentienceGladiator::processMaze(const MazeSquare &maze)
{
    metrics_t metrics = {};

    fillNeighborsMetrics(maze, metrics);
    std::sort(metrics.begin(), metrics.end(), std::greater<>());
}