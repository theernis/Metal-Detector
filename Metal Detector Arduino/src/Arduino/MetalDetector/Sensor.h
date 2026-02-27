#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{
private:
  int _pin;
  int _treshold = 511;
  bool _enabled = true;
public:
  Sensor(int pin);
  ~Sensor();
  int readValue();
  void setTreshold(int treshold);
  int getTreshold();
  void setEnabled(bool enabled);
};

#endif