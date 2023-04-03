#include "FloorSensor.h"
#include "Elevator.h"
#include <iostream>
#include <QObject>

// constructor
FloorSensor::FloorSensor(Elevator *elevator) : elevator(elevator)
{
    qInfo("[Floor Sensor %d] Initialized ", elevator->getCarNum());
}

void FloorSensor::findFloor(int floorNum)
{

    qInfo("[Floor Sensor %d] Found floor %d ", elevator->getCarNum(), floorNum);
    elevator->setCurrentFloor(floorNum);
}
