#include <iostream>
#include <QObject>
#include <QTime>
#include <QCoreApplication>
#include <QTime>

#include "Elevator.h"
#include "ButtonPanel.h"
#include "Door.h"
#include "FloorSensor.h"
#include "Display.h"
#include "Audio.h"
#include "WeightSensor.h"
// CONSTRUCTOR
Elevator::Elevator(int carNum, int floorNums, ElevatorControlSystem *ecs) : carNum(carNum), floorNums(floorNums), ecs(ecs), currentFloor(0), emergencyStop(false)
{

    panel = new ButtonPanel(this, floorNums);
    door = new Door(this);
    floorSens = new FloorSensor(this);
    displaySystem = new Display(this);
    audioSystem = new Audio(this);
    weightSensor = new WeightSensor(this);

    qInfo("[Elevator %d] initialized", carNum);
}

// DESTRUCTOR
Elevator::~Elevator()
{
    delete panel;
    delete door;
    delete floorSens;
    delete displaySystem;
    delete audioSystem;

    qInfo("[Elevator %d] destroyed", carNum);
}

// GETTERS AND SETTERS
int Elevator::getCarNum()
{
    return carNum;
}

FloorSensor *Elevator::getFloorSens()
{
    return floorSens;
}

Door *Elevator::getDoor()
{
    return door;
}

ButtonPanel *Elevator::getPanel()
{
    return panel;
}

Display* Elevator::getDisplay(){
    return displaySystem;
}

int Elevator::getCurrentFloor(){
    return currentFloor;
}

//Sets the current floor of the elevator to the given floor number and updates the elevator position in the Elevator Control System.
void Elevator::setCurrentFloor(int floorNum)
{

    currentFloor = floorNum; // Set current floor to the given floor number
    qInfo("[Elevator %d] current floor: %d", carNum, currentFloor); // Print elevator and current floor info to console
    ecs->updateElevatorPosition(carNum, currentFloor); // Update elevator position in Elevator Control System
}

//Sets the current floor of the elevator to the given floor number and updates the elevator position in the Elevator Control System.
void Elevator::setEmergencyStop(bool stop)
{

    emergencyStop = stop;
 }

// METHODS

//called when a button inside the elevator is pressed indicating that a passenger wants to go to a specific floor.
void Elevator::pressButton(int floorNum)
{
    qInfo("[Elevator %d] pressed floor button %d", carNum, floorNum);

    // Call the handleElevatorRequest function of the ElevatorControlSystem object
    ecs->handleElevatorRequest(carNum, floorNum);
}

void Elevator::move(int direction)
{
    qInfo("[Elevator %d] emergency stop: %d", carNum, emergencyStop);
    if(emergencyStop){
        qInfo("[Elevator %d] cannot move", carNum);
    } else{
        // If direction is 0, move up
        if (direction == 0)
        {
            qInfo("[Elevator %d] move up", carNum); // Output a log message indicating the elevator is moving up
            floorSens->findFloor(currentFloor + 1); // Call the findFloor() method of the floor sensor to update the elevator's current floor
        }
        // If direction is 1, move down
        else if (direction == 1)
        {
            qInfo("[Elevator %d] move down", carNum); // Output a log message indicating the elevator is moving down
            floorSens->findFloor(currentFloor - 1); // Call the findFloor() method of the floor sensor to update the elevator's current floor
        }

    }



}

// a fire alert is received from the Elevator Control System
void Elevator::fire()
{
    // Log the elevator's response to the fire alert and display a message on the elevator's display
    qInfo("[Elevator %d] Fire Alert from ECS, moving to lowest floors", carNum);


    // Move the elevator to the lowest floors by decrementing the current floor until it reaches the ground floor
    for (int i = currentFloor; i > 0; i--)
    {
        move(1);
    }

    // Display a power outage on the elevator's display

    audioSystem->fireDisplay();
}

void Elevator::powerOutage()
{
    // Log the elevator's response to the fire alert and display a message on the elevator's display
    qInfo("[Elevator %d] Fire Alert from ECS, moving to lowest floors", carNum);


    // Move the elevator to the lowest floors by decrementing the current floor until it reaches the ground floor
    for (int i = currentFloor; i > 0; i--)
    {
        move(1);
    }

    // Display a power outage on the elevator's display

    audioSystem->powerOutageDisplay();
}

void Elevator::stop(){
    qInfo("[Elevator %d] Stopped", carNum);
    door->open();

}

void Elevator::resolved(){
    door->open();
    qInfo("[Elevator %d] Floor Request Resolved", carNum);
    door->close();


}

void Elevator::obstaclesWarning(){
    emergencyStop=true;
    qInfo("[Elevator %d] Obstacles Warning", carNum);
    audioSystem->obstaclesDisplay();

    stop();
    //door->getDoorSensor()->removeObstacles();
}



void Elevator::overload(){
    emergencyStop=true;
    weightSensor->overload();

    stop();
    qInfo("[Elevator %d] Overload Warning. Remove Weight", carNum);
    audioSystem->overloadDisplay();


}

void Elevator::help(){
    qInfo("[Elevator %d] connecting to safety services", (carNum));
    qInfo("[Elevator %d] Call connected", carNum);
    qInfo("[Elevator %d] Hello...(Wait 5 seconds for response)", carNum);
    QTime time= QTime::currentTime().addSecs(5);
       while (QTime::currentTime() < time) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

       qInfo("[Elevator %d] User is not responding, contacting emergency services.", carNum);

    ecs->getHelp();
}
