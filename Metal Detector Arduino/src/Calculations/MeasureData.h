#ifndef MEASUREDATA_H
#define MEASUREDATA_H

#include <cmath>
#include "FastComparisons.h"

// structure for storing single sensor data
struct SensorData
{
    float enterTime_s = NAN;
    float exitTime_s = NAN;
    bool hasEntered = false;
    bool hasExited = false;
};

// structure for storing measured data
struct MeasureData
{
    int count;
    SensorData* sensorData = nullptr;
};

// resets (or initializes) MeasureData struct
void resetMeasurements(MeasureData* data, int sensorCount);
// validates MeasureData struct to confirm enough data is collected
bool validateMeasurements(MeasureData* data);
// cleans up MeasureData struct by freeing allocated memory
void cleanupMeasurements(MeasureData* data);

#endif