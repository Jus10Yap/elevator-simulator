#include "ElevatorControlSystem.h"
#include "Elevator.h"
#include "Floor.h"
#include "OpportunisticStrategy.h"
#include "AllocationStrategy.h"
#include <iostream>

// CONSTRUCTOR
ElevatorControlSystem::ElevatorControlSystem(int numFloors, int numElevators)
    : numFloors(numFloors), numElevators(numElevators)
{

    init(numFloors, numElevators);

}

// DECONSTRUCTOR
ElevatorControlSystem::~ElevatorControlSystem()
{
    // Deallocate elevator requests
    for (int i = 0; i < numElevators; i++)
        delete[] elevatorRequests[i];
    delete[] elevatorRequests;

    // Deallocate floor requests
    for (int i = 0; i < numFloors; i++)
        delete[] floorRequests[i];
    delete[] floorRequests;

    // Deallocate elevators
    for (int i = 0; i < numElevators; i++)
        delete elevators[i];

    // Deallocate floors
    for (int i = 0; i < numFloors; i++)
        delete floors[i];
}

// init function
void ElevatorControlSystem::init(int numFloors, int numElevators)
{
    // initialize all the elevators' request
    elevatorRequests = new int *[numElevators];
    for (int i = 0; i < numElevators; i++)
    {
        elevatorRequests[i] = new int[numFloors];
        std::fill_n(elevatorRequests[i], numFloors, 0);
    }
    qInfo("[ECS] Initialized all elevator requests");

    // initialize all the floors' request
    floorRequests = new int *[numFloors];
    for (int i = 0; i < numFloors; i++)
    {
        floorRequests[i] = new int[2];
        std::fill_n(floorRequests[i], 2, 0);
    }
    qInfo("[ECS] Initialized all floor requests");

    // initialize all the elevators
    for (int i = 0; i < numElevators; i++)
    {
        elevators[i] = new Elevator(i, numFloors, this);
    }
    qInfo("[ECS] Initialized all elevators");

    // initalize all the floors of the building
    for (int i = 0; i < numFloors; i++)
    {
        floors[i] = new Floor(i, this);
    }
    qInfo("[ECS] Initialized all floors");

    // initalize all the elevator positions to floor 0
    for (int i = 0; i < numElevators; i++)
    {
        elevatorPositions[i] = 0;
    }
    qInfo("[ECS] Initialized all elevator positions");

    prevDirections = new int[numElevators];
    std::fill_n(prevDirections, numElevators, 0);
    strat = new OpportunisticStrategy();

}

// GETTERS AND SETTERS
int ElevatorControlSystem::getNumElevators()
{
    return numElevators;
}
int ElevatorControlSystem::getNumFloors()
{
    return numFloors;
}

void ElevatorControlSystem::setNumElevators(int elevators)
{
    numElevators = elevators;
}
void ElevatorControlSystem::setNumFloors(int floors)
{
    numFloors = floors;
}

//returns position for specified elevator number
int ElevatorControlSystem::getElevatorPositions(int carNum)
{
    return elevatorPositions[carNum];
}
// returns elevator for specified elevator number
Elevator* ElevatorControlSystem::getElevator(int carNum){

    return elevators[carNum];
}


// METHODS

//simulates the movement of elevators
void ElevatorControlSystem::directions()
{
    qInfo("[ECS] Here is the next step.");



    int* directions = strat->coordinateElevators(floorRequests, elevatorRequests, numFloors, numElevators, elevators, floors, prevDirections);



    simulateElevatorPositions(directions);

    prevDirections= directions;
}

//handles the elevator requests made from a floor.
void ElevatorControlSystem::handleElevatorRequest(int elevatorNum, int floorNum)
{
        // Output log message indicating that an elevator request is being handled
        qInfo("[ECS] Handling elevator request");

        // Set the value at the corresponding index in the elevatorRequests data structure to 1 to reflect the new request
        elevatorRequests[elevatorNum][floorNum] = 1;


        notify();
}

//handles the floor requests made from inside an elevator
void ElevatorControlSystem::handleFloorRequest(int floorNum, int direction)
{
    qInfo("[ECS] Handling floor request at %d with direction %d", floorNum, direction);

    int direction_index;

    // determine the index of the direction in the floorRequests array
    if (direction == 1) { // if direction is down
        direction_index = 1; // set index to 1
    } else { // otherwise (direction is up)
        direction_index = 0; // set index to 0
    }

    // set the floor request at the specified floor and direction index to 1
    floorRequests[floorNum][direction_index] = 1;

    for(int i=0; i<numElevators;i++){
        if(elevators[i]->getCurrentFloor() == floorNum){
            qInfo("[ECS] Elevator %d handled floor %d", elevators[i], floorNum);
            elevators[i]->resolved();
        }
    }
}

// updates the position of an elevator and updates MainWindow
void ElevatorControlSystem::updateElevatorPosition(int elevatorNum, int floorNum)
{


    //update elevator position
    elevatorPositions[elevatorNum] = floorNum;
    qInfo("[ECS] Updated Elevator %d position to floor number %d", elevatorNum, floorNum);

    //check if elevator needs to stop at this floor
    if(elevatorRequests[elevatorNum][floorNum]){
        elevators[elevatorNum]->stop();
        elevators[elevatorNum]->resolved();
    }

    //check if any floor request has been resolved
    bool resolved = false;

    if(floorRequests[floorNum][0]){
        floorRequests[floorNum][0] = 0;
        floors[floorNum]->resolvedRequest(0);
        resolved = true;
    }

    if(floorRequests[floorNum][1]){
        floors[floorNum]->resolvedRequest(1);
        resolved = true;
    }

    //if floor rq has been resolved, stop elevator
    if(resolved){
        elevators[elevatorNum]->stop();
        elevators[elevatorNum]->resolved();

    }
    //notify mainwindow
       notify();

}
//simulates the movement of elevators.
void ElevatorControlSystem::simulateElevatorPositions(int* directions)
{

    for (int i = 0; i < numElevators; i++)
    {
        elevators[i]->move(directions[i]);
    }

}

//simulates a fire alert and moves all elevators to floor 0
void ElevatorControlSystem::fireAlert(int carNum)
{
    if(carNum == -1){
        for (int i = 0; i < numElevators; i++)
        {
            qInfo("[ECS] Reported FIRE in the Building");
            elevators[i]->fire();


        }
        qInfo("[ECS] All Elevators have moved to Floor 0");

    } else{
        qInfo("[ECS] Reported FIRE in Elevator Number %d", carNum);

        // Move carNum elevators to floor 0
        elevators[carNum]->fire();
        qInfo("[ECS] Elevator %d have moved to Floor 0", carNum);


    }

}

//simulates a power outage and moves all elevators to floor 0
void ElevatorControlSystem::powerOutageAlert()
{
    qInfo("[ECS] Reported POWER OUTAGE.");

    // Move all elevators to floor 0
    for (int i = 0; i < numElevators; i++)
    {
        elevators[i]->powerOutage();
    }

    qInfo("[ECS] All Elevators have moved to Floor 0");
}

void ElevatorControlSystem::getHelp(){
    qInfo("[ECS] Contacted Emergency Services");
}
