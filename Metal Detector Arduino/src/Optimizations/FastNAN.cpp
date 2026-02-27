#include "FastNAN.h"

bool fastIsNAN(float var)
{
    return ((NAN != NAN) ? var != var : std::isnan(var));
}