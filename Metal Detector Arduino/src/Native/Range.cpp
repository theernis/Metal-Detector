#include <Range.h>

Range createRange(float start, float end, float step)
{
    Range range;
    range.start = start;
    range.end = end;
    range.step = step;
    range.stepCount = (int)((end - start) / step);
    return range;
}

float getRangeValue(Range range, int index)
{
    return range.start + index * range.step;
}