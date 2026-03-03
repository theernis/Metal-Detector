#include "ProcessPiece.h"

void processPiece(Piece piece, bool* enabled, SimulationData* data)
{
    static MeasureData measureData;
    int sensor_count = 6;
    resetMeasurements(&measureData, sensor_count);
    calculateMeasurementData(&measureData, enabled, piece);
    Measurement measurement = processMeasuredData(measureData);
    *data = (SimulationData){piece, measureData, measurement};
}

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