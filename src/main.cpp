#include "gladiator.h"
#include "../include/PathFinder.hpp"
#include <csignal>
#include "../include/Bomb.hpp"

#define ROBOT_ID 80

#if defined(ROBOT_ID) && ROBOT_ID == 79
    #define DELTA_X 0.0047
    #define DELTA_Y -0.0046
#elif defined(ROBOT_ID) && ROBOT_ID == 80
    #define DELTA_X  0.0028
    #define DELTA_Y -0.0069
#endif

Gladiator *gladiator = nullptr;

#define DEG2RAD(x) (x * 0.01745329252)
#define RAD2DEG(x) (x * 57.2957795131)

Control control;

void reset()
{
    delay(10);
    gladiator->log("Call of reset function");
}

void setup()
{
    gladiator = new Gladiator();
    gladiator->game->onReset(&reset);
}

void gloop() {
    auto tmp = navigation::findClosestBombPath(gladiator->maze->getNearestSquare(), {{0, 0}, {12, 12}});
    gladiator->log("Bomb: %u %u", tmp->i, tmp->j);
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
