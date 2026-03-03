#ifndef FASTNAN_H
#define FASTNAN_H

#include <cmath>

inline float minFloat(float a, float b)
{
    return (a < b) ? a : b;
}

inline float maxFloat(float a, float b)
{
    return (a > b) ? a : b;
}

inline float absFloat(float var)
{
    return (var < 0) ? -var : var;
}

inline bool fastIsNAN(float var)
{
    return ((NAN != NAN) ? var != var : std::isnan(var));
}

#endif