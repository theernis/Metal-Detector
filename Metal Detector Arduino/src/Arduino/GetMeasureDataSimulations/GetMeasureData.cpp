#include "GetMeasureData.h"


// simulated piece data
int pieceIndex = 0;

// collects measurements from sensors
void collectMeasurements(MeasureData* data, MetalDetectorArray* sensors) {
    if (millis()%1000 != 0 || pieceCount == 0)
    {
        return;
    }
    // collect data
    calculateMeasurementData(data, sensors->_enabled, pieces[pieceIndex]);
    // reset data in case of invalid data
    if (!data->sensorData[0]->hasExited && data->sensorData[3]->hasExited) {
        resetMeasurements(data, data->count);
    }
    // roll next piece
    pieceIndex = (pieceIndex+1)%pieceCount;
}