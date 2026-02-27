#ifndef MEASUREDATA_H
#define MEASUREDATA_H

#include <cmath>
#include "FastNAN.h"

struct SensorData {
  float enterTime_s = NAN;
  float exitTime_s = NAN;
  bool hasEntered = false;
  bool hasExited = false;
};

struct MeasureData {
  int count;
  SensorData* sensorData = nullptr;
};

void resetMeasurements(MeasureData* data, int sensorCount);
bool validateMeasurements(MeasureData* data);

#endif