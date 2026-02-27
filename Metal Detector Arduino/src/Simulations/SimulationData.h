#ifndef SIMULATIONDATA_H
#define SIMULATIONDATA_H

#include "FastTrigonometry.h"

struct Angle
{
    float angle_deg; // deg
    float angle_rad; // rad
    float sinVal;
    float cosVal;
    float tanVal;
};

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

Angle angleDeg(float angle_deg);
Angle angleRad(float angle_rad);

#endif