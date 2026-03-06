#include "MetalDetector.h"

// constructor
MetalDetectorArray::MetalDetectorArray(int count)
{
    _count = count;
    _sensors = new Sensor*[count];
    for (int i = 0; i < count; i++)
    {
        _sensors[i] = nullptr;
    }
    
}

// destructor
MetalDetectorArray::~MetalDetectorArray()
{
    delete[] _sensors;
}

// get amount of sensors
int MetalDetectorArray::getCount()
{
    return _count;
}

// set sensor pin
void MetalDetectorArray::setSensor(int index, int pin)
{
    if (index >= 0 && index < _count)
    {
        if (_sensors[index] != nullptr)
        {
            delete _sensors[index];
        }
        _sensors[index] = new Sensor(pin);
    }
}

// read measurement of a sensor
int MetalDetectorArray::readSensor(int index)
{
    if (index >= 0 && index < _count)
    {
        return _sensors[index]->readValue();
    }
    return -1;
}

// set treshold of a sensor
void MetalDetectorArray::setThreshold(int index, int threshold)
{
    if (index >= 0 && index < _count)
    {
        _sensors[index]->setTreshold(threshold);
    }
}

// get treshold of a sensor
int MetalDetectorArray::getThreshold(int index)
{
    if (index >= 0 && index < _count)
    {
        return _sensors[index]->getTreshold();
    }
    return -1;
}

// enable/disable a sensor
void MetalDetectorArray::setEnabled(int index, bool enabled)
{
    if (index >= 0 && index < _count)
    {
        _sensors[index]->setEnabled(enabled);
    }
}