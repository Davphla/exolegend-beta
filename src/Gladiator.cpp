#include "Gladiator.hpp"
#include <algorithm>
#include <map>
#include <vector>

using coordinate_t = std::pair<int, int>;
using score_t = uint;

static score_t getCaseScore(const MazeSquare &maze)
{
    score_t count = 0;

    count += maze.northSquare != nullptr;
    count += maze.southSquare != nullptr;
    count += maze.westSquare != nullptr;
    count += maze.eastSquare != nullptr;
    return count;
}

static void fillNeighborsScores(const MazeSquare &maze,
                                std::map<coordinate_t, score_t> &scores)
{
    score_t current_square_score = getCaseScore(maze);
    const std::vector<MazeSquare *> neighbors = {maze.northSquare, maze.southSquare,
                                           maze.westSquare, maze.eastSquare};
    for (MazeSquare *neighbor : neighbors) {
        if (neighbor != nullptr) {
            coordinate_t coord = {neighbor->i, neighbor->j};
            scores[coord] = getCaseScore(*neighbor);
        }
    }
}

void getScore(const MazeSquare &maze)
{
    std::map<coordinate_t, score_t> neighbors;

    fillNeighborsScores(maze, neighbors);
    std::sort(neighbors.begin(), neighbors.end(), std::greater<>());
}