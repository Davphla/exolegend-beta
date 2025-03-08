#include "gladiator.h"

struct coordinate_t {
    int x;
    int y;
};

struct square_metric_t {
    uint score;   // closest neighboor
    uint nb_visit;// nb time player visit this square
};

using metrics_t = std::map<coordinate_t, square_metric_t>;

using bomb_t = bool;
using score_t = uint;


class SentienceGladiator : public Gladiator {
    void processMaze(const MazeSquare &maze);
};