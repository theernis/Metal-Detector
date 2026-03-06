#include "FastTrigonometry.h"

#include <iostream>

#define ENABLE_LOOKUP
// ENABLE_MISS_COUNT must be disable for multithreading
//#define ENABLE_MISS_COUNT

#ifdef ENABLE_MISS_COUNT
long long int call = 0;
long long int miss = 0;
#endif

float* sinLookupTable = nullptr;
float* cosLookupTable = nullptr;
float* tanLookupTable = nullptr;

void generateSinLookupTable()
{
    // create lookup table
    if (sinLookupTable == nullptr)
    {
        sinLookupTable = new float[360];
        for (int i = 0; i < 360; i++)
        {
            sinLookupTable[i] = sinf(RAD(i));
        }
    }
    return;
}

void generateCosLookupTable()
{
    // create lookup table
    if (cosLookupTable == nullptr)
    {
        cosLookupTable = new float[360];
        for (int i = 0; i < 360; i++)
        {
            cosLookupTable[i] = cosf(RAD(i));
        }
    }
    return;
}

void generateTanLookupTable()
{
    // create lookup table
    if (tanLookupTable == nullptr)
    {
        tanLookupTable = new float[180];
        for (int i = 0; i < 180; i++)
        {
            tanLookupTable[i] = tanf(RAD(i));
        }
    }
    return;
}

// generates lookup tables
void generateLookupTables()
{
    generateSinLookupTable();
    generateCosLookupTable();
    generateTanLookupTable();
    return;
}

// deletes lookup tables
void deleteLookupTables()
{
    delete[] sinLookupTable;
    sinLookupTable = nullptr;
    delete[] cosLookupTable;
    cosLookupTable = nullptr;
    delete[] tanLookupTable;
    tanLookupTable = nullptr;
    
    #ifdef ENABLE_MISS_COUNT
    call = 0;
    miss = 0;
    #endif
    return;
}

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

    if (sinLookupTable == nullptr)
    {
        generateSinLookupTable();
    }

    // return from lookup table if possible
    // '(float)(int)deg' is a very fast way to check if the number is an integer
    if (deg == (float)(int)deg)
    {
        return sinLookupTable[((int)deg)%360 + ((deg < 0) ? 360 : 0)];
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

    if (cosLookupTable == nullptr)
    {
        generateCosLookupTable();
    }

    // return from lookup table if possible
    // '(float)(int)deg' is a very fast way to check if the number is an integer
    if (deg == (float)(int)deg)
    {
        return tanLookupTable[((int)deg)%360 + ((deg < 0) ? 360 : 0)];
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

    if (tanLookupTable == nullptr)
    {
        generateTanLookupTable();
    }

    // return from lookup table if possible
    // '(float)(int)deg' is a very fast way to check if the number
    if (deg == (float)(int)deg)
    {
        return tanLookupTable[((int)deg)%180 + ((deg < 0) ? 180 : 0)];
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