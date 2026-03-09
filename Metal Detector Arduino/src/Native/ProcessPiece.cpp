#include "ProcessPiece.h"
#include <iostream>

// process data->piece and calculate measurements
// returns processed data in SimulationData struct
void processPiece(bool* enabled, SimulationData* data)
{
    int sensor_count = 6;
    resetMeasurements(data->measureData, sensor_count);
    calculateMeasurementData(data->measureData, enabled, data->piece);
    data->measurement = processMeasuredData(*data->measureData);
}

// test function to process all pieces from SimulationData and output results
void test(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    bool enabled[] = {true, true, true, true, true, true};
    SimulationData data;
    data.measureData = new MeasureData;
    data.measureData->sensorData = nullptr;
    for (int i = 0; i < pieceCount; i++)
    {
        data.piece = pieces[i];
        processPiece(enabled, &data);
        processOutput(&data);
    }
    cleanupMeasurements(data.measureData);
    delete data.measureData;
}