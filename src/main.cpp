#include "../include/Bomb.hpp"
#include "../include/PathFinder.hpp"
#include "Gladiator.hpp"
#include "Vector.hpp"
#include "gladiator.h"
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
void go_to(Gladiator *gladiator, Position cons, Position pos);

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
    gladiator->weapon->dropBombs(gladiator->weapon->getBombCount());
}

void gloop()
{
    depositBomb();
    MazeSquare square = *gladiator->maze->getNearestSquare();
    sentience.processMaze(square);

    for (auto [coords, metric]: sentience.metrics) {
        if (metric.no_bomb > 0) {
            gladiator->log("Bomb on %d - %d", coords.first, coords.second);
        }
    }
    coordinate_t coords = sentience.findClosestBomb(square);
    auto realPosition= mazeToReal(coords);

    gladiator->log("Bomb coordinates: (%f, %f)", coords.first, coords.second);
    go_to(gladiator, {realPosition.x, realPosition.y, 0},
          gladiator->robot->getData().position);
    //gladiator->log("Bomb: %u %u", tmp->i, tmp->j);
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
