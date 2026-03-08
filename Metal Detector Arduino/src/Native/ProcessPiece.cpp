#include "ProcessPiece.h"
#include <iostream>

// process piece data and calculate measurements
// returns processed data in SimulationData struct
void processPiece(Piece piece, bool* enabled, SimulationData* data)
{
    data->piece = piece;
    int sensor_count = 6;
    resetMeasurements(data->measureData, sensor_count);
    calculateMeasurementData(data->measureData, enabled, piece);
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
        processPiece(pieces[i], enabled, &data);
        processOutput(&data);
    }
    cleanupMeasurements(data.measureData);
    delete data.measureData;
}