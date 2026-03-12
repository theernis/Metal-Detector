#include "GetMeasureData.h"


// collects measurements from sensors
void collectMeasurements(MeasureData* data, MetalDetectorArray* sensors)
{
    // collect data
    for (int i = 0; i < data->count; i++)
    {
        float sensorData = sensors->readSensor(i);
        // collect enter times
        if (!data->sensorData[i]->hasEntered && sensorData > sensors->getThreshold(i))
        {
            data->sensorData[i]->enterTime_s = millis() / 1000.0f;
            data->sensorData[i]->hasEntered = true;
        }
        // collect exit times
        if (data->sensorData[i]->hasEntered && !data->sensorData[i]->hasExited && sensorData <= sensors->getThreshold(i))
        {
            data->sensorData[i]->exitTime_s = millis() / 1000.0f;
            data->sensorData[i]->hasExited = true;
        }
    }
    // reset data in case of invalid data
    if (!data->sensorData[0]->hasExited && data->sensorData[3]->hasExited)
    {
        resetMeasurements(data, data->count);
    }
}