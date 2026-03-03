#include "SimulationData.h"

int pieceCount = 18;
Piece pieces[] = {
    {0.50f, 0.20f, 0.20f, angleDeg(00.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(05.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(10.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(15.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(20.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(25.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(30.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(35.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(40.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(45.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(50.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(55.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(60.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(65.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(70.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(75.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(80.00f), 0.00f},
    {0.50f, 0.20f, 0.20f, angleDeg(85.00f), 0.00f},
};

Angle angleDeg(float angle_deg)
{
    return (Angle){angle_deg, (float)RAD(angle_deg), fastSinDeg(angle_deg), fastCosDeg(angle_deg), fastTanDeg(angle_deg)};
}

Angle angleRad(float angle_rad)
{
    return (Angle){(float)DEG(angle_rad), angle_rad, fastSinRad(angle_rad), fastCosRad(angle_rad), fastTanRad(angle_rad)};
}