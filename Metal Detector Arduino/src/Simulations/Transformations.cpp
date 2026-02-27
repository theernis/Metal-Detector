#include "Transformations.h"

// simulated sensors positions
Position sensorPositions[] = {{0.00f, 0.4f}, {-0.16f, 0.00f}, {-0.08f, 0.00f}, {0.00f, 0.00f}, {0.08f, 0.00f}, {0.16f, 0.00f}};

// point transformation
Position T(Position P, Position C, float sinVal, float cosVal) {
    float x = P.x-C.x;
    float y = P.y-C.y;
    
    return (Position){x*cosVal-y*sinVal, x*sinVal+y*cosVal};
}

// treshold < 1 point is inside the piece
// treshold = 1 point is on the edge of a piece
// treshold > 1 point is outside the piece
float treshold(Position relativePoint, Piece piece) {
    float xDistance = ((xDistance = relativePoint.x/piece.width_m) < 0) ? -xDistance : xDistance;
    float yDistance = ((yDistance = relativePoint.y/piece.length_m) < 0) ? -yDistance : yDistance;

    return 2 * ((xDistance > yDistance) ? xDistance : yDistance);
}