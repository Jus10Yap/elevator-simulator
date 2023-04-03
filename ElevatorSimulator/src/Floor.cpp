#include "Floor.h"
#include "DirectionButton.h"

Floor::Floor(int floorNumber, ElevatorControlSystem *ecs)
    : check(true), floorNum(floorNumber), ecs(ecs)
{

    // initializing all direction buttons
    directionButton[0] = new DirectionButton(this, 0); // up
    directionButton[1] = new DirectionButton(this, 1); // down
    qInfo("[Floor %d] Initialized all Direction Buttons", floorNum);
}

Floor::~Floor()
{
    for (int i = 0; i < 2; i++)
    {
        delete directionButton[i];
    }
}

void Floor::notifyECS(int direction)
{
    if (direction == 0)
    {
        directionButton[0]->lightsOn();
        qInfo("[Floor %d] Turn ON up lights", floorNum);
    }
    else if (direction == 1)
    {
        directionButton[1]->lightsOn();
        qInfo("[Floor %d] Turn ON down lights", floorNum);
    }
    ecs->handleFloorRequest(floorNum, direction);
    qInfo("[Floor %d] Notified ECS to go %d", floorNum, direction);
}

void Floor::resolvedRequest(int direction)
{
    if (direction == 0)
    {
        directionButton[0]->lightsOff();
        qInfo("[Floor %d] Turn OFF up lights", floorNum);
    }
    else if (direction == 1)
    {
        directionButton[1]->lightsOff();
        qInfo("[Floor %d] Turn OFF down lights", floorNum);
    }

    qInfo("[Floor %d] direction button %d resolved request", floorNum, direction);
}


