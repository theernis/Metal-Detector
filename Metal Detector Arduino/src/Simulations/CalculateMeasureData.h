#ifndef CALCULATEMEASUREDATA_H
#define CALCULATEMEASUREDATA_H

#include <cmath>

#include "SimulationData.h"
#include "MeasureData.h"
#include "Transformations.h"
#include "FastTrigonometry.h"

void calculateMeasurementData(MeasureData* data, bool* enabled, Piece piece);

#endif