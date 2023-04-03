#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger
{
private:
    int weight;           // the weight of the passenger in pounds
    int floorDestination; // the floor number that the passenger wants to go to

public:
    // Constructor
    Passenger(int weight, int floorDestination);

    // Destructor
    ~Passenger();

    // Getters
    int getWeight() const;
    int getFloorDestination() const;

    // Setters
    void setWeight(int weight);
    void setFloorDestination(int floorDestination);

    // Other methods
    void pressed(int floorDestination);
    // Simulates the action of a passenger pressing a button to request the elevator to stop at their desired floor
};

#endif
