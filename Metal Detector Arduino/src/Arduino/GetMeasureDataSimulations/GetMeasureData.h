#ifndef GETMEASUREDATA_H
#define GETMEASUREDATA_H

#include "MetalDetector.h"
#include "MeasureData.h"
#include "CalculateMeasureData.h"

// collects measurements from sensors
void collectMeasurements(MeasureData* data, MetalDetectorArray* sensors);

#endif