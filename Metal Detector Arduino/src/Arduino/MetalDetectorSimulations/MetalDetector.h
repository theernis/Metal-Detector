#ifndef METALDETECTOR_H
#define METALDETECTOR_H

#include "Arduino.h"
#include "SimulationData.h"
#include "Transformations.h"

class MetalDetectorArray
{
private:
    int _count;
    bool* _enabled = nullptr;
public:
    MetalDetectorArray(int count);
    ~MetalDetectorArray();
    int getCount();
    void setSensor(int index, int pin);
    int readSensor(int index);
    void setThreshold(int index, int threshold);
    int getThreshold(int index);
    void setEnabled(int index, bool enabled);
};

#endif