#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <string>
#include "ElevatorControlSystem.h"

class ButtonPanel;
class Door;
class FloorSensor;
class Display;
class Audio;
class WeightSensor;
class Elevator
{
private:
    int carNum;    // The number of the elevator car
    int floorNums; // The number of the current floor of car
    int currentFloor;// the current floor the elevator is in
    bool emergencyStop;        // Whether the elevator is in emergency stop mode
    ElevatorControlSystem *ecs; //Elevators ecs
    ButtonPanel *panel;     // The button panel inside the elevator
    Door *door;             // The door of the elevator
    FloorSensor *floorSens; // The floor sensor used to detect the current floor of the elevator
    Display *displaySystem; // The display system used to show floor numbers and emergency messages
    Audio *audioSystem;         // The audio system used to alert passengers of emergencies
    WeightSensor* weightSensor;// The weight sensor used to detect the current weight of the elevator


public:
    // Constructor
    Elevator(int carNum, int numFloors, ElevatorControlSystem *ecs);
    // Deconstructor
    ~Elevator();

    // Getters and Seters
    int getCarNum();
    FloorSensor *getFloorSens();
    Door *getDoor();
    ButtonPanel *getPanel();
    Display* getDisplay();
    void setCurrentFloor(int floorNum);
    int getCurrentFloor();
    void setEmergencyStop(bool stop);

    // Methods
    void pressButton(int floorNum);  // Press a button inside the elevator car to request a floor
    void requestFloor(int floorNum); // Add a floor to the list of requested floor
    void move(int direction);// Move the elevator up or down
    void fire();        // Set the fire attribute to true and activate the fire alarm
    void powerOutage(); // Set the powerOutage attribute to true and activate the backup power
    void stop();                     // Stop the elevator
    void resolved();// resolved request
    void obstaclesWarning();                // obstacles in elevator door
    void overload();// overload in elevator weight sensor
    void help();//user pressed help

};

#endif // ELEVATOR_H
