#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

#include "Subject.h"
#include "defs.h"
class Elevator;
class Floor;
class AllocationStrategy;

class ElevatorControlSystem : public Subject
{
private:
  int numFloors;          // Number of floors in the building
  int numElevators;       // Number of Elevators in the building
  int **elevatorRequests; // 2d array of elevator requests to their respective current floors
  int **floorRequests;    // 2d array of floor requests to their respective current floors
  int elevatorPositions[MAX_ELEVATORS];
  int* prevDirections;
  Floor *floors[MAX_FLOORS];          // array of 24 floor objects
  Elevator *elevators[MAX_ELEVATORS]; // array of 24 elevator objects
  AllocationStrategy* strat;

public:
  // Constructor
  ElevatorControlSystem(int numFloors, int numElevators);
  // Deconstructor
  ~ElevatorControlSystem();

  void init(int numFloors, int numElevators);

  // getters and setters
  int getNumElevators();
  int getNumFloors();
  void setNumFloors(int floors);
  void setNumElevators(int elevators);
  int getElevatorPositions(int carNum);
  Elevator* getElevator(int carNum);

  // METHODS
  void directions();

  void handleElevatorRequest(int elevatorNum, int floorNum);

  void handleFloorRequest(int floorNum, int direction);

  //updates position of elevator
  void updateElevatorPosition(int elevatorNum, int floorNum);

  //moves all elevators based on aloc strat
  void simulateElevatorPositions(int* directions);

  // Fire alert button pressed in elevator carNum
  void fireAlert(int carNum);

  // Power outage in elevator carNum
  void powerOutageAlert();

  //user did not respond and reach emergency services
   void getHelp();

};

#endif // ELEVATORCONTROLSYSTEM_H
