#ifndef OPPORTUNISTICSTRATEGY_H
#define OPPORTUNISTICSTRATEGY_H

#include "AllocationStrategy.h"

class OpportunisticStrategy: public AllocationStrategy
{
  public:
    virtual ~OpportunisticStrategy();
    virtual int* coordinateElevators(int** floorRequests, int ** elevatorRequests, int floorNums, int elevatorNums, Elevator *elevators[MAX_ELEVATORS], Floor *floors[MAX_FLOORS], int* prevDirections);
};
#endif // OPPORTUNISTICSTRATEGY_H
