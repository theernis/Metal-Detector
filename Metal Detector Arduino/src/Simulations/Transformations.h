#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <cmath>
#include "SimulationData.h"
#include "FastTrigonometry.h"

#ifndef PI
#define PI M_PI
#endif

struct Position
{
    float x;
    float y;
};

// simulated sensors positions
extern Position sensorPositions[];

// point transformation operations
Position T(Position P, Position C, float sinVal, float cosVal);

// treshold < 1 point is inside the piece
// treshold = 1 point is on the edge of a piece
// treshold > 1 point is outside the piece
float treshold(Position relativePoint, Piece piece);

#endif