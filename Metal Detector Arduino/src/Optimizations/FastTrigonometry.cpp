#include "FastTrigonometry.h"

#include <iostream>

#define ENABLE_LOOKUP
#define ENABLE_MISS_COUNT

#ifdef ENABLE_MISS_COUNT
long long int call = 0;
long long int miss = 0;
#endif

float fastSinRad(float rad)
{
    return fastSinDeg(DEG(rad));
}

float fastCosRad(float rad)
{
    return fastCosDeg(DEG(rad));
}

float fastTanRad(float rad)
{
    return fastTanDeg(DEG(rad));
}

float fastSinDeg(float deg)
{
    #ifdef ENABLE_MISS_COUNT
    call++;
    #endif
    #ifdef ENABLE_LOOKUP
    static float* lookupTable = nullptr;
    if (lookupTable == nullptr)
    {
        lookupTable = new float[360];
        for (int i = 0; i < 360; i++)
        {
            lookupTable[i] = sinf(RAD(i));
        }
    }

    if (deg == (float)(int)deg)
    {
        return lookupTable[((int)deg)%360 + ((deg < 0) ? 360 : 0)];
    }
    #endif
    
    #ifdef ENABLE_MISS_COUNT
    miss++;
    #endif
    return sinf(RAD(deg));
}

float fastCosDeg(float deg)
{
    #ifdef ENABLE_MISS_COUNT
    call++;
    #endif
    #ifdef ENABLE_LOOKUP
    static float* lookupTable = nullptr;
    if (lookupTable == nullptr)
    {
        lookupTable = new float[360];
        for (int i = 0; i < 360; i++)
        {
            lookupTable[i] = cosf(RAD(i));
        }
    }

    if (deg == (float)(int)deg)
    {
        return lookupTable[((int)deg)%360 + ((deg < 0) ? 360 : 0)];
    }
    #endif
    
    #ifdef ENABLE_MISS_COUNT
    miss++;
    #endif
    return cosf(RAD(deg));
}

float fastTanDeg(float deg)
{
    #ifdef ENABLE_MISS_COUNT
    call++;
    #endif
    #ifdef ENABLE_LOOKUP
    static float* lookupTable = nullptr;
    if (lookupTable == nullptr)
    {
        lookupTable = new float[180];
        for (int i = 0; i < 180; i++)
        {
            lookupTable[i] = tanf(RAD(i));
        }
    }

    if (deg == (float)(int)deg)
    {
        return lookupTable[((int)deg)%180 + ((deg < 0) ? 180 : 0)];
    }
    #endif
    
    #ifdef ENABLE_MISS_COUNT
    miss++;
    #endif
    return tanf(RAD(deg));
}

void missCount()
{
    #ifdef ENABLE_MISS_COUNT
    std::cout << miss << "/" << call << std::endl;
    #endif
}