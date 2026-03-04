#ifndef METALDETECTOR_H
#define METALDETECTOR_H

#include "Arduino.h"
#include "SimulationData.h"
#include "Transformations.h"

// class for metal detector array
class MetalDetectorArray
{
private:
    int _count;
    bool* _enabled = nullptr;
public:
    // constructor
    MetalDetectorArray(int count);
    // destructor
    ~MetalDetectorArray();
    // get amount of sensors
    int getCount();
    // here for compatibility
    void setSensor(int index, int pin);
    // simulate measurement of a sensor
    int readSensor(int index);
    // here for compatibility
    void setThreshold(int index, int threshold);
    // here for compatibility
    int getThreshold(int index);
    // enable/disable a sensor
    void setEnabled(int index, bool enabled);
};

#endif