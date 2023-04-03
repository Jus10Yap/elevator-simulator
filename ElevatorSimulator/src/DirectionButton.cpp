#include "DirectionButton.h"
#include "Floor.h"

// Constructor
DirectionButton::DirectionButton(Floor *floorNum, int direction) : floorNum(floorNum), direction(direction)
{
}

// Pressed function to activate the button
void DirectionButton::pressed()
{
    qInfo("[DirectionButton] %d button is pressed!", direction);
    floorNum->notifyECS(direction);
    lightsOn();
}

// lights on
void DirectionButton::lightsOn()
{
    qInfo("[DirectionButton] lights on!");
    isPressed = true;
}

// lights off
void DirectionButton::lightsOff()
{
    qInfo("[DirectionButton] lights off!");
    isPressed = false;
}
