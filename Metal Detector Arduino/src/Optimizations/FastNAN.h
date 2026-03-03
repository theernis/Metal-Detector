#ifndef FASTNAN_H
#define FASTNAN_H

#include <cmath>

inline bool fastIsNAN(float var)
{
    return ((NAN != NAN) ? var != var : std::isnan(var));
}

#endif