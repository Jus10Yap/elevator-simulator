#ifndef WEIGHT_SENSOR_H
#define WEIGHT_SENSOR_H

class Elevator;

// Weight sensor class
class WeightSensor
{
public:
  // Constructor
  WeightSensor(Elevator* elevator);

  // Overload the weight sensor
  void overload();

  // Remove overload from the weight sensor
  void removeOverload();

private:
  // Maximum weight capacity of the sensor
  int maxWeight;

  Elevator* elevator;
};
#endif // WEIGHT_SENSOR_H
