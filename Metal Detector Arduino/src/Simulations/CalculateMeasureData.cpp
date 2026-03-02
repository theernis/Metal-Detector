#include "CalculateMeasureData.h"

// calculate sensor data for a sensor
void calculateSensorData(SensorData* sensorData, int sensorIndex, Piece* piece)
{
    Piece _piece = *piece;
    // calculate the position of the sensor relative to the piece
    Position relativePoint = T(sensorPositions[sensorIndex], {_piece.horizontalOffset_m, 0}, -_piece.angle.sinVal, _piece.angle.cosVal);

    // calculate intersection points of the piece with the sensor line
    Position collisionPoints[4];
    float x = _piece.width_m/2;
    float y = _piece.length_m/2;
    collisionPoints[0] = {x, ((x-relativePoint.x)/_piece.angle.tanVal+relativePoint.y)};
    collisionPoints[1] = {-x, ((-x-relativePoint.x)/_piece.angle.tanVal+relativePoint.y)};
    collisionPoints[2] = {((y-relativePoint.y)*_piece.angle.tanVal+relativePoint.x), y};
    collisionPoints[3] = {((-y-relativePoint.y)*_piece.angle.tanVal+relativePoint.x), -y};

    // determine entry and exit points
    float entryPoint = NAN;
    float exitPoint = NAN;
    for (int i = 0, j = 0; i < 4 && j < 2; i++)
    {
        if (!(fastIsNAN(collisionPoints[i].x) || fastIsNAN(collisionPoints[i].y)))
        {
            float edgeDistance = treshold(collisionPoints[i], *piece) - 1;
            edgeDistance = (edgeDistance > 0) ? edgeDistance : -edgeDistance;
            if (edgeDistance <= 0.00001f)
            {
                // calculate distance to the collision point along the piece's movement direction and determine if it's an entry or exit point
                float temp = (collisionPoints[i].x-relativePoint.x)*_piece.angle.sinVal+(collisionPoints[i].y-relativePoint.y)*_piece.angle.cosVal;
                if (j == 0)
                {
                    entryPoint = temp;
                }
                else
                {
                    if (entryPoint > temp)
                    {
                        exitPoint = entryPoint;
                        entryPoint = temp;
                    }
                    else
                    {
                        exitPoint = temp;
                    }
                }

                j++;
            }
        }
    }

    if (!(fastIsNAN(entryPoint) && fastIsNAN(exitPoint)))
    {
        float entryTime = entryPoint / _piece.speed_m_per_s;
        float exitTime = exitPoint / _piece.speed_m_per_s;

        (*sensorData).enterTime_s = entryTime;
        (*sensorData).exitTime_s = exitTime;
        (*sensorData).hasEntered = true;
        (*sensorData).hasExited = true;
    }
}

// calculate measurement data
void calculateMeasurementData(MeasureData* data, bool* enabled, Piece piece)
{
    for (int i = 0; i < (*data).count; i++)
    {
        if (enabled[i] == true)
        {
            calculateSensorData(&(*data).sensorData[i], i, &piece);
        }
    }
}