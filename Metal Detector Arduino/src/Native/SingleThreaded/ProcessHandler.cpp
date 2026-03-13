#include "ProcessHandler.h"

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

bool* _enabled;

SimulationData data;

bool _printPiece;
bool _printMeasureData;
bool _printMeasurement;

void initializeOutputs(bool printPiece, bool printMeasureData, bool printMeasurement)
{
    _printPiece = printPiece;
    _printMeasureData = printMeasureData;
    _printMeasurement = printMeasurement;
    setOutputs(_printPiece, _printMeasureData, _printMeasurement);
}

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS), bool* enabled)
{
    _enabled = enabled;
    outputFunction = processOutput;
    data.piece = new Piece;
    data.measureData = new MeasureData;
    data.measurement = new Measurement;
    return;
}

// process handling
void processHandler(Piece piece)
{
    // process piece and call output callback
    *data.piece = piece;
    processPiece(_enabled, &data);
    outputFunction(&data);
}

// cleanup after process handling
void cleanupHandler()
{
    cleanupMeasurements(data.measureData);
    delete data.piece;
    delete data.measureData;
    delete data.measurement;
    return;
}