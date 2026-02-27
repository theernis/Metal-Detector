#ifndef RANGE_H
#define RANGE_H

struct Range
{
    float start;
    float end;
    float step;
    int stepCount;
};

struct PieceRange
{
    Range speed;
    Range length;
    Range width;
    Range angle;
    Range horizontalOffset;
};

Range createRange(float start, float end, float step);
float getRangeValue(Range range, int index);

#endif