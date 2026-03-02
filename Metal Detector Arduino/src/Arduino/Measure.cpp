#include "Measure.h"


const Measurement empty;

Measurement measure(MetalDetectorArray* sensors)
{
    static MeasureData data;
    data.count = sensors->getCount();
    if (sensors == nullptr)
    {
        return empty;
    }
    
    // initialize data
    if (data.sensorData == nullptr)
    {
        resetMeasurements(&data, data.count);
    }

    collectMeasurements(&data, sensors);

    // calculate measurements if sufficient data is collected
    if (validateMeasurements(&data))
    {
        Measurement result = processMeasuredData(data);
        resetMeasurements(&data, data.count);
        return result;
    }
    return empty;
}