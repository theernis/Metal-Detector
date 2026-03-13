#ifndef PROCESSPIECE_H
#define PROCESSPIECE_H

#include "SimulationData.h"
#include "CalculateMeasureData.h"
#include "MeasurementCalculations.h"
#include "Range.h"
#include "Output.h"

// process piece data and calculate measurements
// returns processed data in SimulationData struct
void processPiece(bool* enabled, SimulationData* data);

#endif