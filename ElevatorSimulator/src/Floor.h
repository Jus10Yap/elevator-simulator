#ifndef FLOOR_H
#define FLOOR_H

#include <QObject>
#include "ElevatorControlSystem.h"

class DirectionButton;

class Floor
{

public:
    // Construct a new Floor object with the given floor number
    Floor(int floorNumber, ElevatorControlSystem *ecs);

    ~Floor();

    void notifyECS(int direction);

    void resolvedRequest(int direction);


private:
    int floorNum; // The number of this floor
    ElevatorControlSystem *ecs;
    bool check;
    DirectionButton *directionButton[2]; // up and down

};

#endif
