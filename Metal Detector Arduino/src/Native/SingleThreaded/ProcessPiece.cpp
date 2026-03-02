#include "ProcessPiece.h"

void processPiece(Piece piece, bool* enabled, void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    static MeasureData data;
    int sensor_count = 6;
    resetMeasurements(&data, sensor_count);
    calculateMeasurementData(&data, enabled, piece);
    Measurement measurement = processMeasuredData(data);
    SimulationData simData = {piece, data, measurement};
    processOutput(&simData);
}

void test(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    bool enabled[] = {true, true, true, true, true, true};
    for (int i = 0; i < pieceCount; i++)
    {
        processPiece(pieces[i], enabled, processOutput);
    }
    
}