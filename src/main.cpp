#include "../include/Bomb.hpp"
#include "../include/PathFinder.hpp"
#include "Gladiator.hpp"
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

std::pair<float, float> getGoodBombCoordinate(coordinate_t coord)
{

    auto squareSize = gladiator->maze->getSquareSize();
    float x = (coord.first) * squareSize + (squareSize / 2);
    float y = (coord.second) * squareSize + (squareSize / 2);

    return std::pair<float, float>(x, y);
}

void gloop()
{
    MazeSquare square = *gladiator->maze->getNearestSquare();
    sentience.processMaze(square);
    coordinate_t coords = sentience.findClosestBomb(square);
    std::pair<float, float> real_coords = getGoodBombCoordinate(coords);

    gladiator->log("Real bomb coordinates: (%f, %f)", coords.first, coords.second);
    go_to(gladiator, {real_coords.first, real_coords.second, 0},
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
