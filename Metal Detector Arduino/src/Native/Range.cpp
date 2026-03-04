#include <Range.h>

// functions for creating Range struct
Range createRange(float start, float end, float step)
{
    Range range;
    range.start = start;
    range.end = end;
    range.step = step;
    range.stepCount = (int)((end - start) / step);
    return range;
}

// get value from range by index
float getRangeValue(Range range, int index)
{
    return range.start + index * range.step;
}