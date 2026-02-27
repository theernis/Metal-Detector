#include "MetalDetector.h"

// constructor
MetalDetectorArray::MetalDetectorArray(int count)
{
    _count = count;
    _enabled = new bool[count];
    for (int i = 0; i < count; i++)
    {
        _enabled[i] = true;
    }
}

// destructor
MetalDetectorArray::~MetalDetectorArray()
{
    if (_enabled != nullptr)
    {
        delete[] _enabled;
    }
}

// get amount of sensors
int MetalDetectorArray::getCount()
{
    return _count;
}

// here for compatibility
void MetalDetectorArray::setSensor(int index, int pin)
{
    return;
}

// here for compatibility
int MetalDetectorArray::readSensor(int index)
{
    // validate index
    if (index < 0 || index > _count) {
        return -1;
    }
    
    return 0;
}

// here for compatibility
void MetalDetectorArray::setThreshold(int index, int threshold)
{
    return;
}


// here for compatibility
int MetalDetectorArray::getThreshold(int index)
{
    if (index >= 0 && index < _count) {
        return 511;
    }
    return -1;
}

// enable/disable a sensor
void MetalDetectorArray::setEnabled(int index, bool enabled)
{
    if (index >= 0 && index < _count) {
        _enabled[index] = enabled;
    }
}