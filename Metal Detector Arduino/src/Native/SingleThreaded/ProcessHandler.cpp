#include "ProcessHandler.h"

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

bool* _enabled;

SimulationData data;

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS), bool* enabled)
{
    _enabled = enabled;
    outputFunction = processOutput;
    data.measureData = new MeasureData;
    return;
}

// process handling
void processHandler(Piece piece)
{
    // process piece and call output callback
    processPiece(piece, _enabled, &data);
    outputFunction(&data);
}

// cleanup after process handling
void cleanupHandler()
{
    cleanupMeasurements(data.measureData);
    delete data.measureData;
    return;
}