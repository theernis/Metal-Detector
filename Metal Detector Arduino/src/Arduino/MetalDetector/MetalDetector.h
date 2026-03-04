#ifndef METALDETECTOR_H
#define METALDETECTOR_H

#include "Sensor.h"

// class for metal detector array
class MetalDetectorArray
{
private:
    int _count;
    Sensor** _sensors;
public:
    // constructor
    MetalDetectorArray(int count);
    // destructor
    ~MetalDetectorArray();
    // get amount of sensors
    int getCount();
    // set sensor pin
    void setSensor(int index, int pin);
    // read measurement of a sensor
    int readSensor(int index);
    // set treshold of a sensor
    void setThreshold(int index, int threshold);
    // get treshold of a sensor
    int getThreshold(int index);
    // enable/disable a sensor
    void setEnabled(int index, bool enabled);
};

#endif