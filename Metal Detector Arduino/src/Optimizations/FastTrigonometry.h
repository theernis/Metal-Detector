#ifndef FASTTRIGONOMETRY_H
#define FASTTRIGONOMETRY_H

#include <cmath>

#ifndef PI
#define PI M_PI
#endif

// convert radians to degrees
#define DEG(a) (a/PI*180.0f)
// convert degrees to radians
#define RAD(a) (a*PI/180.0f)

// made these functions to optimize trigonometric calculations by using lookup tables for integer degree values
// did this because I often call the same trigonometric functions with the same values
// so this speeds up the calculations significantly

// generates lookup tables
void generateLookupTables();
// deletes lookup tables
void deleteLookupTables();

// sine from radians
float fastSinRad(float rad);
// cosine from radians
float fastCosRad(float rad);
// tangent from radians
float fastTanRad(float rad);
// sine from degrees
float fastSinDeg(float deg);
// cosine from degrees
float fastCosDeg(float deg);
// tangent from degrees
float fastTanDeg(float deg);

// print lookup miss ratio
void missCount();

#endif