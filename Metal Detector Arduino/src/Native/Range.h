#ifndef RANGE_H
#define RANGE_H

// linear range definition for parameter sweeps in simulations
struct Range
{
    float start;
    float end;
    float step;
    int stepCount;
};

// range definition for pieces in simulations
struct PieceRange
{
    Range speed;
    Range length;
    Range width;
    Range angle;
    Range horizontalOffset;
};

// functions for creating Range struct
Range createRange(float start, float end, float step);
// get value from range by index
float getRangeValue(Range range, int index);

#endif