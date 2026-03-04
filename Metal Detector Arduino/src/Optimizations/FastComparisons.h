#ifndef FASTNAN_H
#define FASTNAN_H

#include <cmath>

// managed to get a bit of performance increase by implementing own versions of some math functions

// min function for floats
inline float minFloat(float a, float b)
{
    return (a < b) ? a : b;
}

// max function for floats
inline float maxFloat(float a, float b)
{
    return (a > b) ? a : b;
}

// absolute value function for floats
inline float absFloat(float var)
{
    return (var < 0) ? -var : var;
}

// fast check for NAN values
inline bool fastIsNAN(float var)
{
    // this works because NAN is the only value that is not equal to itself
    // but to avoid compiler optimizations that might break this, we also check if the value is NAN using std::isnan
    return ((NAN != NAN) ? var != var : std::isnan(var));
}

#endif