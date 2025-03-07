#include "gladiator.h"
Gladiator *gladiator;

#define ROBOT_ID 80

#if defined(ROBOT_ID) && ROBOT_ID == 79
    #define DELTA_X 0.0047
    #define DELTA_Y -0.0046
#elif defined(ROBOT_ID) && ROBOT_ID == 80
    #define DELTA_X  0.0028
    #define DELTA_Y -0.0069
#endif 

void reset()
{
    // fonction de reset:
    // initialisation de toutes vos variables avant le début d'un match
    gladiator->log("Call of reset function"); // GFA 4.5.1
}

void setup()
{
    // instanciation de l'objet gladiator
    gladiator = new Gladiator();
    // enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset); // GFA 4.4.1
    gladiator->game->enableFreeMode(RemoteMode::OFF);
}

void loop()
{
    MazeSquare ms;
    gladiator->robot->setCalibrationOffset(DELTA_X, DELTA_Y, 0); //TODO CHANGE A CALIBRATION OFFSET
    gladiator->control->setWheelSpeed(WheelAxis::LEFT, 0.2); 
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.2);

    if (gladiator->game->isStarted())
    { // tester si un match à déjà commencer
        // code de votre stratégie
        gladiator->log("Hello world - Game Started"); // GFA 4.5.1
    }
    else
    {
        gladiator->log("Hello world - Game not Startd yet"); // GFA 4.5.1
    }
    delay(300);
}
