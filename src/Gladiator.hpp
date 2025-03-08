#include <unordered_map>
#include <map>
#include "../include/utils.hpp"
#include "gladiator.h"
#include <map>
#include <vector>

using path_t = int;

struct square_metric_t {
    uint score;   // closest neighboor
    uint nb_visit;// nb time player visit this square
    uint no_bomb;
    bool is_visited;
    path_t path;
    float final_score;
    coordinate_t coords;
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
    void calculateBestEntry(const MazeSquare &maze);


    void processMaze(const MazeSquare &maze);

    metrics_t metrics = {};
    uint shrink_value = 0;
    std::vector<square_metric_t> best_entries;

    static const uint NB_ENTRY = 5;
    static const uint MAP_SIZE = 11;
};
