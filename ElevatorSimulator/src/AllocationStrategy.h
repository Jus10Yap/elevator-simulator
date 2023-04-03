#ifndef ALLOCATIONSTRATEGY_H
#define ALLOCATIONSTRATEGY_H

#include "Floor.h"
#include "Elevator.h"

class AllocationStrategy {
public:
  ~AllocationStrategy();
  virtual int* coordinateElevators(int** floorRequests, int ** elevatorRequests, int floorNums, int elevatorNums, Elevator *elevators[MAX_ELEVATORS], Floor *floors[MAX_FLOORS], int* prevDirections)=0;
};
#endif // ALLOCATIONSTRATEGY_H
