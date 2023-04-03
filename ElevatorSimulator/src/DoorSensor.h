#ifndef DOOR_SENSOR_H
#define DOOR_SENSOR_H

class Door;

class DoorSensor
{
public:
    // Constructor
    DoorSensor(Door *door);

    bool getObstacles();

    // Check if there are any obstacles blocking the door
    void obstacles();

    // Remove any obstacles blocking the door
    void removeObstacles();

private:
    Door *door;
    bool isObstacle;
};

#endif
