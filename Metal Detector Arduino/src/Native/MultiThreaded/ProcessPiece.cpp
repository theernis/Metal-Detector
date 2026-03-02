#include "ProcessPiece.h"

SimulationData processPiece(Piece piece, bool* enabled)
{
    static MeasureData data;
    int sensor_count = 6;
    resetMeasurements(&data, sensor_count);
    calculateMeasurementData(&data, enabled, piece);
    Measurement measurement = processMeasuredData(data);
    return (SimulationData){piece, data, measurement};
}

void test(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    bool enabled[] = {true, true, true, true, true, true};
    for (int i = 0; i < pieceCount; i++)
    {
        SimulationData data = processPiece(pieces[i], enabled);
        processOutput(&data);
    }
    
}