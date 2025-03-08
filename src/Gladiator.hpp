#include "gladiator.h"
#include <vector>
#include <map>
#include "../include/utils.hpp"

struct square_metric_t {
    uint score;   // closest neighboor
    uint nb_visit;// nb time player visit this square
};

class SentienceGladiator {
    public:
    using bomb_metric_t = std::vector<coordinate_t>;
    using metrics_t = std::map<coordinate_t, square_metric_t>;
    using bomb_t = bool;
    using score_t = uint;

    score_t getCaseScore(const MazeSquare &maze);
    void fillNeighborsMetrics(const MazeSquare &maze);
    void checkSquare(const MazeSquare &maze, square_metric_t &cur);
    coordinate_t findClosestBomb(MazeSquare &cur);

    void processMaze(const MazeSquare &maze);

    metrics_t metrics = {};
    bomb_metric_t bomb_metrics = {};
};
