#ifndef MEASURE_H
#define MEASURE_H

#include "MetalDetector.h"
#include "GetMeasureData.h"
#include "MeasurementCalculations.h"

// collect data and calculate measurements if enough data is collected
Measurement measure(MetalDetectorArray* sensors);

#endif