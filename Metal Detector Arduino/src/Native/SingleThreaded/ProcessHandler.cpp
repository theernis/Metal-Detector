#include "ProcessHandler.h"

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

bool* _enabled;

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS), bool* enabled)
{
    _enabled = enabled;
    outputFunction = processOutput;
    return;
}

// process handling
void processHandler(Piece piece)
{
    // process piece and call output callback
    SimulationData data;
    processPiece(piece, _enabled, &data);
    outputFunction(&data);
    cleanupMeasurements(&data.measureData);
}

// cleanup after process handling
void cleanupHandler()
{
    // no cleanup
    return;
}