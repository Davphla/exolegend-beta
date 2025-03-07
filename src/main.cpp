#include "gladiator.h"
#include "../include/PathFinder.hpp"
#include <csignal>
#include <utility>
#include "../include/Vector.hpp"

#include <valgrind/valgrind.h>
#include <valgrind/memcheck.h>

__attribute__((constructor))
void initFunction() {
    VALGRIND_DISABLE_ERROR_REPORTING;
}

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
    gladiator->log("Initialization");
}

void gloop() {
    auto path = navigation::PathFinder::findPath(gladiator->maze->getSquare(0, 0), gladiator->maze->getSquare(11, 11));
    for (auto square : path) {
        gladiator->log("Path %d %d", square->i, square->j);
    }
    exit(0);
    return;
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.5);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, -0.5);
    while (gladiator->game->isStarted()) {
        //auto position = gladiator->robot->getData().position;
        //auto cposition = gladiator->robot->getData().cposition;
        //gladiator->log("Position %f", RAD2DEG(cposition.a));
        // LOGIC HERE
    }
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
