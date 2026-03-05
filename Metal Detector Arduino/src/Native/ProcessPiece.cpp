#include "ProcessPiece.h"

// process piece data and calculate measurements
// returns processed data in SimulationData struct
void processPiece(Piece piece, bool* enabled, SimulationData* data)
{
    MeasureData measureData;
    int sensor_count = 6;
    resetMeasurements(&measureData, sensor_count);
    calculateMeasurementData(&measureData, enabled, piece);
    Measurement measurement = processMeasuredData(measureData);
    *data = (SimulationData){piece, measureData, measurement};
}

// test function to process all pieces from SimulationData and output results
void test(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    bool enabled[] = {true, true, true, true, true, true};
    for (int i = 0; i < pieceCount; i++)
    {
        SimulationData data;
        processPiece(pieces[i], enabled, &data);
        processOutput(&data);
    }
    
}