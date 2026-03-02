#include "MeasureData.h"


// reset measured data
void resetMeasurements(MeasureData* data, int sensorCount)
{
    // set count
    (*data).count = sensorCount;
    // unallocate list
    if ((*data).sensorData != nullptr)
    {
        delete[] (*data).sensorData;
        (*data).sensorData = nullptr;
    }
    // allocate list
    (*data).sensorData = new SensorData[sensorCount];
}

// check if sufficient data is collected
bool validateMeasurements(MeasureData* data)
{
    bool allExited = true;
    for (int i = 0; i < (*data).count; i++)
    {
        if ((*data).sensorData[i].hasEntered != (*data).sensorData[i].hasExited)
        {
            allExited = false;
        }
    }

    return (allExited && (*data).sensorData[3].hasExited && (*data).sensorData[0].exitTime_s < (*data).sensorData[3].exitTime_s);
}