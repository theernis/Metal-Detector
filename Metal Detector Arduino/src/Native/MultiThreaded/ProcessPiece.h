#ifndef PROCESSPIECE_H
#define PROCESSPIECE_H

#include "SimulationData.h"
#include "CalculateMeasureData.h"
#include "MeasurementCalculations.h"
#include "Range.h"
#include "Output.h"

SimulationData processPiece(Piece piece, bool* enabled);
void test(void (*processOutput)(SimulationData*));

#endif