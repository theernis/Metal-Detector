#include "Sensor.h"

// constructor
Sensor::Sensor(int pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
}

// destructor
Sensor::~Sensor()
{
}

// get measured value
int Sensor::readValue()
{
    if (!_enabled) {
        return 0;
    }
    return analogRead(_pin);
}

// set treshold
void Sensor::setTreshold(int treshold)
{
    _treshold = treshold;
}

// get treshold
int Sensor::getTreshold()
{
    return _treshold;
}

// enable/disable sensor
void Sensor::setEnabled(bool enabled)
{
    _enabled = enabled;
}