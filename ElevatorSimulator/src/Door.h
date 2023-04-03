#ifndef DOOR_H
#define DOOR_H

#include "Bell.h"
#include "DoorSensor.h"

class Elevator;

class Door
{
public:
  // Constructor for the ElevatorDoor class.
  Door(Elevator *elevator);

  // Deconstructor
  ~Door();

  int getDoorNum();

  DoorSensor* getDoorSensor();

  // Opens the elevator door
  void open();

  // Closes the elevator door
  void close();

  // if there are any obstacles blocking the door
  void obstacles();

  // Remove any obstacles blocking the door
  void removeObstacles();


private:
  Elevator *elevator;
  Bell *bell;
  DoorSensor *sens;
  // Whether the elevator door is currently open.
  bool isOpen;
};

#endif
