#include <unordered_map>
#include <map>
#include "../include/utils.hpp"
#include "gladiator.h"
#include <map>
#include <vector>

struct square_metric_t {
    uint score;   // closest neighboor
    uint nb_visit;// nb time player visit this square
    uint no_bomb;
    bool is_visited;
};

class SentienceGladiator {
public:
    using metrics_t = std::map<coordinate_t, square_metric_t>;
    using bomb_t = bool;
    using score_t = uint;

    score_t getCaseScore(const MazeSquare &maze);
    void fillNeighborsMetrics(const MazeSquare &maze);
    void checkSquare(const MazeSquare &maze, square_metric_t &cur);
    coordinate_t findClosestBomb(MazeSquare &cur);
    void reset();

    void processMaze(const MazeSquare &maze);

    metrics_t metrics = {};
    uint shrink_value = 0;
};
