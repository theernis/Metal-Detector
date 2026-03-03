#ifndef MEASUREMENTCALCULATIONS_H
#define MEASUREMENTCALCULATIONS_H

#include <cmath>
#include "MeasureData.h"
#include "FastTrigonometry.h"

struct Measurement
{
    float speed_m_per_s = NAN; // m/s
    float length_m = NAN; // m
    float width_m = NAN; // m
    float angle_deg = NAN; // degrees
};

Measurement processMeasuredData(MeasureData data);

#endif