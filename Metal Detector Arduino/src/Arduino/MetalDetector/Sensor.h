#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Sensor class for storing and retriving sensor data
class Sensor
{
private:
    int _pin;
    int _treshold = 511;
    bool _enabled = true;
public:
    // constructor
    Sensor(int pin);
    // destructor
    ~Sensor();
    // get measured value
    int readValue();
    // set treshold
    void setTreshold(int treshold);
    // get treshold
    int getTreshold();
    // enable/disable sensor
    void setEnabled(bool enabled);
};

#endif