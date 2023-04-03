#include "OpportunisticStrategy.h"
#include "AllocationStrategy.h"

OpportunisticStrategy::~OpportunisticStrategy(){

}
int* OpportunisticStrategy::coordinateElevators(int** floorRequests, int ** elevatorRequests, int floorNums, int elevatorNums, Elevator *elevators[MAX_ELEVATORS], Floor *floors[MAX_FLOORS], int* prevDirections){
    //initialize directions
    int* elevatorDirections  = new int[elevatorNums];
    int currentFloor;

    for(int i = 0; i < elevatorNums; i++){
            int currentFloor = elevators[i]->getCurrentFloor();

            if(currentFloor == 0){
                elevatorDirections[i] = 0; // prioritize going up if elevator is at first floor
            } else if(currentFloor == (floorNums-1)){
                elevatorDirections[i] = 1; // prioritize going down if elevator is at top floor
            } else {
                elevatorDirections[i] = prevDirections[i]; // continue in the previous direction
            }
        }

    return elevatorDirections;
}
