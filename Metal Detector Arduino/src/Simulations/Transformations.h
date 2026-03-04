#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <cmath>
#include "SimulationData.h"
#include "FastTrigonometry.h"
#include "FastComparisons.h"

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
// returns the position of point P relative to center point C rotated by the angle defined by sinVal and cosVal
// its easier to check if apoint is inside a square after being rotated around it,
// rather than rotating the square and checking if the point is inside it
Position T(Position P, Position C, float sinVal, float cosVal);

// treshold < 1 point is inside the piece
// treshold = 1 point is on the edge of a piece
// treshold > 1 point is outside the piece
float treshold(Position relativePoint, Piece piece);

#endif