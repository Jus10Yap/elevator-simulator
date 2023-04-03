#ifndef FLOOR_SENSOR_H
#define FLOOR_SENSOR_H

#include "Elevator.h"

class FloorSensor
{
private:
  Elevator *elevator;

public:
  FloorSensor(Elevator *elevator);
  // detect the current floor and compare it to the input 'floorNum'
  void findFloor(int floorNum);
};

#endif
