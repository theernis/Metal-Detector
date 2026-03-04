#ifndef PROCESSPIECE_H
#define PROCESSPIECE_H

#include "SimulationData.h"
#include "CalculateMeasureData.h"
#include "MeasurementCalculations.h"
#include "Range.h"
#include "Output.h"

// process piece data and calculate measurements
// returns processed data in SimulationData struct
void processPiece(Piece piece, bool* enabled, SimulationData* data);

// test function to process all pieces from SimulationData and output results
void test(void (*processOutput)(OUTPUT_FUNCTION_ARGS));

#endif