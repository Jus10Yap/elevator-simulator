#include <QObject>

#include "Door.h"
#include "Elevator.h"

// Constructor for the ElevatorDoor class.
Door::Door(Elevator *elevator) : elevator(elevator), isOpen(false)
{

    bell = new Bell(this);
    sens = new DoorSensor(this);
}

// Deconstructor
Door::~Door()
{
    delete sens;
    delete bell;
}

int Door::getDoorNum()
{
    return elevator->getCarNum();
}

DoorSensor* Door::getDoorSensor(){
    return sens;
}

// Opens the elevator door
void Door::open()
{
    isOpen = true;
    qInfo("[Door %d] Doors opened.", elevator->getCarNum());
    bell->ring();
}

// Closes the elevator door
void Door::close()
{
    if (sens->getObstacles() == false)
    {
        isOpen = false;

        qInfo("[Door %d] Doors closed.", elevator->getCarNum());
        bell->ring();
    } else {
        qInfo("[Door %d] Doors cannot close", elevator->getCarNum());
        open();
    }
}

// if there are any obstacles blocking the door
void Door::obstacles()
{
    isOpen = true;
    elevator->setEmergencyStop(true);
    qInfo("[Door %d] there are obstacles", elevator->getCarNum());
    // 3 attempts
    for (int i = 0; i < 3; i++)
    {
        qInfo("[Door %d] remove obstacles attempt number %d", elevator->getCarNum(), (i + 1));
        close();
        if (sens->getObstacles() == false)
        {
            removeObstacles();

        }
    }
    if (sens->getObstacles() == true)
    {
        elevator->obstaclesWarning();
    }

}

// Remove any obstacles blocking the door
void Door::removeObstacles()
{
    qInfo("[Door %d] removed obstacles", elevator->getCarNum());
    isOpen = false;
    elevator->setEmergencyStop(false);
    close();
}
