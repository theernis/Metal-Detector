#include "ProcessPiece.h"

// process data->piece and calculate measurements
// returns processed data in SimulationData struct
void processPiece(bool* enabled, SimulationData* data)
{
    int sensor_count = 6;
    resetMeasurements(data->measureData, sensor_count);
    calculateMeasurementData(data->measureData, enabled, *data->piece);
    *data->measurement = processMeasuredData(*data->measureData);
}