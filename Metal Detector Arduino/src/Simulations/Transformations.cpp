#include "Transformations.h"

// simulated sensors positions
Position sensorPositions[] = {{0.00f, 0.4f}, {-0.16f, 0.00f}, {-0.08f, 0.00f}, {0.00f, 0.00f}, {0.08f, 0.00f}, {0.16f, 0.00f}};

// point transformation
// returns the position of point P relative to center point C rotated by the angle defined by sinVal and cosVal
// its easier to check if apoint is inside a square after being rotated around it,
// rather than rotating the square and checking if the point is inside it
Position T(Position P, Position C, float sinVal, float cosVal)
{
    float x = P.x-C.x;
    float y = P.y-C.y;
    
    return (Position){x*cosVal-y*sinVal, x*sinVal+y*cosVal};
}

// treshold < 1 point is inside the piece
// treshold = 1 point is on the edge of a piece
// treshold > 1 point is outside the piece
float treshold(Position relativePoint, Piece piece)
{
    float xDistance = relativePoint.x/piece.width_m;
    xDistance = absFloat(xDistance);
    float yDistance = relativePoint.y/piece.length_m;
    yDistance = absFloat(yDistance);

    return 2 * maxFloat(xDistance, yDistance);
}