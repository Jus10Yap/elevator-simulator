#include<QObject>
#include "DoorSensor.h"
#include "Door.h"
// Constructor
DoorSensor::DoorSensor(Door* door): door(door), isObstacle(false){

}

bool DoorSensor::getObstacles(){
    return isObstacle;
}

// Check if there are any obstacles blocking the door
void DoorSensor::obstacles(){
    qInfo("[Door Sensor %d] There are obstacles detected! Please remove them.", door->getDoorNum());

    isObstacle = true;
    door->obstacles();

}

// Remove any obstacles blocking the door
void DoorSensor::removeObstacles(){
    qInfo("[Door Sensor %d] Removed Obstacles..", door->getDoorNum());
    isObstacle= false;
    door->removeObstacles();

}


