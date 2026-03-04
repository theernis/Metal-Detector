#include "ProcessHandler.h"

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    outputFunction = processOutput;
    return;
}

// process handling
void processHandler(Piece piece, bool* enabled)
{
    // process piece and call output callback
    SimulationData data;
    processPiece(piece, enabled, &data);
    outputFunction(&data);
}

// cleanup after process handling
void cleanupHandler()
{
    // no cleanup
    return;
}