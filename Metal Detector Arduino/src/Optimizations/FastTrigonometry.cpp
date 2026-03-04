#include "FastTrigonometry.h"

#include <iostream>

#define ENABLE_LOOKUP
#define ENABLE_MISS_COUNT

#ifdef ENABLE_MISS_COUNT
long long int call = 0;
long long int miss = 0;
#endif

// sine from radians
float fastSinRad(float rad)
{
    return fastSinDeg(DEG(rad));
}

// cosine from radians
float fastCosRad(float rad)
{
    return fastCosDeg(DEG(rad));
}

// tangent from radians
float fastTanRad(float rad)
{
    return fastTanDeg(DEG(rad));
}

// sine from degrees
float fastSinDeg(float deg)
{
    #ifdef ENABLE_MISS_COUNT
    call++;
    #endif
    #ifdef ENABLE_LOOKUP
    // create lookup table
    static float* lookupTable = nullptr;
    if (lookupTable == nullptr)
    {
        lookupTable = new float[360];
        for (int i = 0; i < 360; i++)
        {
            lookupTable[i] = sinf(RAD(i));
        }
    }

    // return from lookup table if possible
    // '(float)(int)deg' is a very fast way to check if the number is an integer
    if (deg == (float)(int)deg)
    {
        return lookupTable[((int)deg)%360 + ((deg < 0) ? 360 : 0)];
    }
    #endif
    
    #ifdef ENABLE_MISS_COUNT
    miss++;
    #endif
    // in case of a lookup miss, calculate the value
    return sinf(RAD(deg));
}

// cosine from degrees
float fastCosDeg(float deg)
{
    #ifdef ENABLE_MISS_COUNT
    call++;
    #endif
    #ifdef ENABLE_LOOKUP
    // create lookup table
    static float* lookupTable = nullptr;
    if (lookupTable == nullptr)
    {
        lookupTable = new float[360];
        for (int i = 0; i < 360; i++)
        {
            lookupTable[i] = cosf(RAD(i));
        }
    }

    // return from lookup table if possible
    // '(float)(int)deg' is a very fast way to check if the number is an integer
    if (deg == (float)(int)deg)
    {
        return lookupTable[((int)deg)%360 + ((deg < 0) ? 360 : 0)];
    }
    #endif
    
    #ifdef ENABLE_MISS_COUNT
    miss++;
    #endif
    // in case of a lookup miss, calculate the value
    return cosf(RAD(deg));
}

// tangent from degrees
float fastTanDeg(float deg)
{
    #ifdef ENABLE_MISS_COUNT
    call++;
    #endif
    #ifdef ENABLE_LOOKUP
    // create lookup table
    static float* lookupTable = nullptr;
    if (lookupTable == nullptr)
    {
        lookupTable = new float[180];
        for (int i = 0; i < 180; i++)
        {
            lookupTable[i] = tanf(RAD(i));
        }
    }

    // return from lookup table if possible
    // '(float)(int)deg' is a very fast way to check if the number
    if (deg == (float)(int)deg)
    {
        return lookupTable[((int)deg)%180 + ((deg < 0) ? 180 : 0)];
    }
    #endif
    
    #ifdef ENABLE_MISS_COUNT
    miss++;
    #endif
    // in case of a lookup miss, calculate the value
    return tanf(RAD(deg));
}

// print lookup miss ratio
void missCount()
{
    #ifdef ENABLE_MISS_COUNT
    std::cout << miss << "/" << call << std::endl;
    #endif
}