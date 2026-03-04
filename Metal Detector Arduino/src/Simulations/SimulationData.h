#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include "FastTrigonometry.h"

// structure for angle with precalculated values
struct Angle
{
    float angle_deg; // deg
    float angle_rad; // rad
    float sinVal;
    float cosVal;
    float tanVal;
};

// structure for simulated piece
struct Piece
{
    float speed_m_per_s; // m/s
    float length_m; // m
    float width_m; // m
    Angle angle;
    float horizontalOffset_m; // m
};

extern int pieceCount;
extern Piece pieces[];

// create angle structure from degree value
Angle angleDeg(float angle_deg);
// create angle structure from radian value
Angle angleRad(float angle_rad);

#endif