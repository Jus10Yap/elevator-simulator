#include "WeightSensor.h"
#include "Elevator.h"

#include <QObject>

WeightSensor::WeightSensor(Elevator *elevator) : elevator(elevator)
{

    qInfo("[WeightSensor %d] Initialized", elevator->getCarNum());
}

void WeightSensor::overload(){

    qInfo("[WeightSensor %d] overload", elevator->getCarNum());
}


