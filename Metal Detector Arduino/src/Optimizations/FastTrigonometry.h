#ifndef FASTTRIGONOMETRY_H
#define FASTTRIGONOMETRY_H

#include <cmath>

#ifndef PI
#define PI M_PI
#endif

#define DEG(a) (a/PI*180.0f)
#define RAD(a) (a*PI/180.0f)

float fastSinRad(float rad);
float fastCosRad(float rad);
float fastTanRad(float rad);
float fastSinDeg(float deg);
float fastCosDeg(float deg);
float fastTanDeg(float deg);
void missCount();

#endif