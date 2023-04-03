#ifndef DIRECTION_BUTTON_H
#define DIRECTION_BUTTON_H

#include "Floor.h"

// Direction Button class for elevator control system
class DirectionButton
{
private:
    Floor *floorNum;
    int direction; // Direction to be set by the button
    // 0 for up
    // 1 for down
    bool isPressed;

public:
    // Constructor
    DirectionButton(Floor *floorNum, int direction);

    // Pressed function to activate the button
    void pressed();

    // lights on
    void lightsOn();

    // lights off
    void lightsOff();
};

#endif
