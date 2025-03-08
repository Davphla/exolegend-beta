#include "../include/Bomb.hpp"
#include "../include/PathFinder.hpp"
#include "Gladiator.hpp"
#include "Vector.hpp"
#include "gladiator.h"
#include "utils.hpp"
#include <csignal>

#define ROBOT_ID 80

#if defined(ROBOT_ID) && ROBOT_ID == 79
    #define DELTA_X 0.0047
    #define DELTA_Y -0.0046
#elif defined(ROBOT_ID) && ROBOT_ID == 80
    #define DELTA_X 0.0028
    #define DELTA_Y -0.0069
#endif

Gladiator *gladiator = nullptr;
SentienceGladiator sentience;

#define DEG2RAD(x) (x * 0.01745329252)
#define RAD2DEG(x) (x * 57.2957795131)

Control control;
void go_to(Position cons, Position pos);

void reset()
{
    delay(10);
    gladiator->log("Call of reset function");
}

void setup()
{
    gladiator = new Gladiator();
    gladiator->game->onReset(&reset);
    sentience = SentienceGladiator();
}

void depositBomb() {
    if (gladiator->weapon->getBombCount() == 0) {
        return;
    }
    gladiator->weapon->dropBombs(gladiator->weapon->getBombCount());
}

void findNewBomb() {
    if (sentience.goal != nullptr) {
        if (sentience.goal->coin.value > 0) {
            return;
        }
    }
    coordinate_t coords = sentience.findClosestBomb(*gladiator->maze->getNearestSquare());
    sentience.goal = gladiator->maze->getSquare(coords.first, coords.second);
    sentience._path = navigation::PathFinder::findPath(gladiator->maze->getNearestSquare(), gladiator->maze->getSquare(coords.first, coords.second));
    gladiator->log("Following path of %ld checkpoint", sentience._path.size());
}

void followPath() {
    if (sentience._path.empty()) {
        return;
    }
    auto realPosition = mazeToReal({sentience._path.back()->i, sentience._path.back()->j});
    go_to({realPosition.x, realPosition.y, 0}, gladiator->robot->getData().position);

    if (sentience._path.back() == gladiator->maze->getNearestSquare()) {
        gladiator->log("Checkpoint");
        sentience._path.pop_back();
    }
}

void gloop()
{
    MazeSquare *square = gladiator->maze->getNearestSquare();
    if (square != nullptr) {
        sentience.processMaze(*square);
    }
    depositBomb();
    findNewBomb();
    followPath();
    static std::time_t start_time = std::time(0);
    std::time_t elapsed_time = std::time(0) - start_time;
    if (elapsed_time >= 15) {
        sentience.shrink_value += 1;
        start_time = std::time(0); // reset start time
    }

    /*coordinate_t coords = {sentience.goal->i, sentience.goal->j};
    auto realPosition = mazeToReal(coords);
    go_to({realPosition.x, realPosition.y, 0},gladiator->robot->getData().position);*/
}

void loop()
{
    gladiator->log("Game status %d", gladiator->game->isStarted());

    if (gladiator->game->isStarted()) {
#ifdef FREE_MODE
        gladiator->game->enableFreeMode(RemoteMode::OFF);
#else
        gladiator->game->enableFreeMode(RemoteMode::ON);
#endif
        gloop();
    }
    delay(200);
}
