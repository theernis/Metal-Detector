#ifndef PROCESSPIECE_H
#define PROCESSPIECE_H

#include "SimulationData.h"
#include "CalculateMeasureData.h"
#include "MeasurementCalculations.h"
#include "Range.h"
#include "Output.h"

void processPiece(Piece piece, bool* enabled, SimulationData* data);
void test(void (*processOutput)(SimulationData*));

#endif