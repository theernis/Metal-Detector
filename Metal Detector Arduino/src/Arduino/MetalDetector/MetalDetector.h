#ifndef METALDETECTOR_H
#define METALDETECTOR_H

#include "Sensor.h"

class MetalDetectorArray
{
private:
    int _count;
    Sensor** _sensors;
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