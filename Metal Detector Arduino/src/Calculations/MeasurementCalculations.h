#ifndef MEASUREMENTCALCULATIONS_H
#define MEASUREMENTCALCULATIONS_H

#include <cmath>
#include "MeasureData.h"
#include "FastTrigonometry.h"

// struct for calculated measurement data
struct Measurement
{
    float speed_m_per_s = NAN; // m/s
    float length_m = NAN; // m
    float width_m = NAN; // m
    float angle_deg = NAN; // degrees
};

// calculate Measurement from MeasureData
Measurement processMeasuredData(MeasureData data);

#endif