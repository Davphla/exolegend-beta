#include "Gladiator.hpp"
#include <algorithm>
#include <map>
#include <vector>

using bomb_t = bool;
using score_t = uint;

struct coordinate_t {
    int x;
    int y;
};

struct square_metric_t {
    uint score;
};

using metrics_t = std::map<coordinate_t, square_metric_t>;


static score_t getCaseScore(const MazeSquare &maze)
{
    score_t count = 0;
    #define ADD_SCORE_IF_POSSESSED(square) \
        count += (square != nullptr && square->possession);

    ADD_SCORE_IF_POSSESSED(maze.northSquare)
    ADD_SCORE_IF_POSSESSED(maze.southSquare)
    ADD_SCORE_IF_POSSESSED(maze.westSquare)
    ADD_SCORE_IF_POSSESSED(maze.eastSquare)
    return count;
}

static void fillNeighborsScores(const MazeSquare &maze,
                                metrics_t &metrics)
{
    score_t current_square_score = getCaseScore(maze);
    const std::vector<MazeSquare *> neighbors = {
        maze.northSquare, maze.southSquare, maze.westSquare, maze.eastSquare};

    for (MazeSquare *neighbor : neighbors) {
        if (neighbor != nullptr) {
            coordinate_t coord = {neighbor->i, neighbor->j};
            square_metric_t &cur = metrics[coord];
            if (cur.score)
                continue;
            cur.score = getCaseScore(*neighbor);
            fillNeighborsScores(*neighbor, metrics);
        }
    }
}

void processMaze(const MazeSquare &maze)
{
    metrics_t metrics = {};

    fillNeighborsScores(maze, metrics);
    std::sort(metrics.begin(), metrics.end(), std::greater<>());
}
