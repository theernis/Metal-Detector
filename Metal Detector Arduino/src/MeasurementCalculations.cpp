#include "MeasurementCalculations.h"


float distanceBetweenSensorInLine_m = 0.08; // m
float distanceToFirstSensor_m = 0.4; // m

// calculate speed
float calculateSpeed_m_per_s(MeasureData data)
{
    return distanceToFirstSensor_m / (data.sensorData[3].exitTime_s - data.sensorData[0].exitTime_s);
}

// calculate length
float calculateLength_m(MeasureData data, float speed_m_per_s)
{
    float time_s = 0;
    float newTime_s = 0;
    // find longest time between enter and exit of sensors in line
    for (int i = 1; i < data.count; i++)
    {
        newTime_s = (data.sensorData[i].exitTime_s - data.sensorData[i].enterTime_s);
        time_s = (newTime_s > time_s) ? newTime_s : time_s;
    }
    return time_s * speed_m_per_s;
}

// calculate width
float calculateWidth_m(MeasureData data)
{
    int countwidth = 0;
    for (int i = 1; i < data.count; i++)
    {
        countwidth += (int)(bool)(data.sensorData[i].hasEntered && data.sensorData[i].hasExited);
    }
    return countwidth * distanceBetweenSensorInLine_m;
}


// calculate angle 
struct Angles
{
    float left_deg; // range -90.00:00.00
    float middle_deg; // range -45.00:45.00
    float right_deg; // range 00.00:90.00
};
float calculateAngle_deg(MeasureData data, float speed_m_per_s)
{
    int angleCount = 0;

    float* angles = new float[data.count-2];
    for (int i = 0; i < data.count - 2; i++)
    {
        if (data.sensorData[i+1].hasEntered && data.sensorData[i+2].hasEntered)
        {
            // angle between two neigboring sensors
            angles[i] = DEG(atanf(((data.sensorData[i+2].enterTime_s - data.sensorData[i+1].enterTime_s) * speed_m_per_s) / distanceBetweenSensorInLine_m));
            angleCount++;
        }
        else
        {
            angles[i] = NAN;
        }
    }

    // return 0 if only a single sensor is triggered
    if (angleCount <= 0)
    {
        delete[] angles;
        return 0;
    }
    

    // testing 3 different angle ranges
    Angles* angleRanges = new Angles[angleCount];
    Angles sum = {0, 0, 0};
    for (int i = 0, j = 0; i < data.count - 2; i++)
    {
        if (!fastIsNAN(angles[i]))
        {
            sum.left_deg += (angleRanges[j].left_deg = angles[i] - ((angles[i] > 0) ? 90 : 0));
            sum.middle_deg += (angleRanges[j].middle_deg = angles[i]);
            sum.right_deg += (angleRanges[j].right_deg = angles[i] + ((angles[i] < 0) ? 90 : 0));
            j++;
        }
    }
    delete[] angles;

    // return angle if only one angle was detected
    if (angleCount == 1)
    {
        delete[] angleRanges;
        return sum.middle_deg;
    }

    // return angle that is closer to 0 if only two angles are detected
    if (angleCount == 2)
    {
        // choose the one closer to 0
        float angle1 = angleRanges[0].middle_deg;
        float angle2 = angleRanges[1].middle_deg;
        delete[] angleRanges;
        if (((angle1 < 0) ? -angle1 : angle1) < ((angle2 < 0) ? -angle2 : angle2))
        {
            return angle1;
        }
        else
        {
            return angle2;
        }
    }

    // find average difference in all three ranges
    Angles average = {sum.left_deg/angleCount, sum.middle_deg/angleCount, sum.right_deg/angleCount};

    Angles diffSum = {0, 0, 0};
    for (int i = 0; i < angleCount; i++)
    {
        float diffLeft = angleRanges[i].left_deg-average.left_deg;
        float diffMiddle = angleRanges[i].middle_deg-average.middle_deg;
        float diffRight = angleRanges[i].right_deg-average.right_deg;
            
        diffSum.left_deg += (diffLeft < 0) ? -diffLeft : diffLeft;
        diffSum.middle_deg += (diffMiddle < 0) ? -diffMiddle : diffMiddle;
        diffSum.right_deg += (diffRight < 0) ? -diffRight : diffRight;
    }
    Angles diffAverage = {diffSum.left_deg/angleCount, diffSum.middle_deg/angleCount, diffSum.right_deg/angleCount};
    // find smallest difference
    float diff = (diffAverage.left_deg < diffAverage.middle_deg) ? diffAverage.left_deg : diffAverage.middle_deg;
    diff = (diff < diffAverage.right_deg) ? diff : diffAverage.right_deg;

    // count average angle excluding anomolies
    float angleSum = 0;
    int newAngleCount = 0;
    // choose a range with smallest difference and exclude anomalies
    if (diff == diffAverage.left_deg)
    {
        for (int i = 0; i < angleCount; i++)
        {
            float tempDiff = (angleRanges[i].left_deg - average.left_deg);
            if (((tempDiff < 0) ? -tempDiff : tempDiff) <= diff)
            {
                angleSum += angleRanges[i].left_deg;
                newAngleCount++;
            }
        }
    }
    else if (diff == diffAverage.middle_deg)
    {
        for (int i = 0; i < angleCount; i++)
        {
            float tempDiff = (angleRanges[i].middle_deg - average.middle_deg);
            if (((tempDiff < 0) ? -tempDiff : tempDiff) <= diff)
            {
                angleSum += angleRanges[i].middle_deg;
                newAngleCount++;
            }
        }
    }
    else
    {
        for (int i = 0; i < angleCount; i++)
        {
            float tempDiff = (angleRanges[i].right_deg - average.right_deg);
            if (((tempDiff < 0) ? -tempDiff : tempDiff) <= diff)
            {
                angleSum += angleRanges[i].right_deg;
                newAngleCount++;
            }
        }
    }
    float averageAngle = angleSum/newAngleCount;
    if (averageAngle > 45)
    {
        averageAngle -= 90;
    }
    if (averageAngle < -45)
    {
        averageAngle += 90;
    }
    
    delete[] angleRanges;
    return averageAngle;
    // I give up this is the 5th concept of angle calculations I tried this night
    // this one at least gets 8/10 right when testing 0-45 degrees in 5 degree intervals
    // UPDATE
    // spent another whole night here, finally got it perfect
    // right now it's 9:15 am, I have to hand it in less than 3 hours
    // another update half an hour later
    // it breaks with smaller pieces
    // 5 minutes later from last line
    // I need at least 4 sensors in line triggering to get a perfect angle
    // the problem is that our group only has 3 in line (and one in the front which doesn't count here)
    // an hour and a half until the deadline
    // implemented patches in case less angles are measured than required
    // biggest variation while testing now went from 0.5 deg to 5 deg
    // also there appears to be sign loss in the same range where variation is the biggest
    // but that is expected when we have less data to work due to fewer sensors being triggered
    // and patches being created last minute
    // an hour to deadline
    // I give up for real this time, I don't think I can improve it any more
}

void adjustOnAngle(Measurement* result, MeasureData data)
{
    if ((*result).angle_deg == 0.00f)
    {
        return;
    }
    float angle = (*result).angle_deg; // rad
    float newLength;
    float newWidth;

    // calculate adjusted length
    newLength = (*result).length_m*fastCosDeg(angle);

    // calculate adjusted width
    int mostLeftIndex = -1;
    int mostRightIndex = -1;
    for (int i = 1; i < data.count; i++)
    {
        if (data.sensorData[i].hasEntered)
        {
            if (mostLeftIndex == -1)
            {
                mostLeftIndex = i;
            }
            mostRightIndex = i;
        }
    }
    float d = ((mostRightIndex - mostLeftIndex) * distanceBetweenSensorInLine_m); // distance between most left and most right sensors
    float x1 = (data.sensorData[mostLeftIndex].exitTime_s - data.sensorData[mostLeftIndex].enterTime_s) * (*result).speed_m_per_s; // length measured by most left sensor
    float x2 = (data.sensorData[mostRightIndex].exitTime_s - data.sensorData[mostRightIndex].enterTime_s) * (*result).speed_m_per_s; // length measured by most right sensor
    newWidth = d/fastCosDeg(angle) + (x1 + x2 - (*result).length_m) * fastSinDeg(angle);
    newWidth = (newWidth < 0) ? -newWidth : newWidth;

    (*result).length_m = newLength;
    (*result).width_m = newWidth;
}

Measurement processMeasuredData(MeasureData data)
{
    Measurement result;

    result.speed_m_per_s = calculateSpeed_m_per_s(data);

    result.length_m = calculateLength_m(data, result.speed_m_per_s);

    result.width_m = calculateWidth_m(data);

    result.angle_deg = calculateAngle_deg(data, result.speed_m_per_s);

    adjustOnAngle(&result, data);

    return result;
}