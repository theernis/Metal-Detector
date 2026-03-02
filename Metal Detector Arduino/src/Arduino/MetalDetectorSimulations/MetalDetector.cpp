#include "MetalDetector.h"

// simulated piece data
const float verticalPieceStart_m = 1.00f;
const float verticalPieceEnd_m = -1.00f;
unsigned long timeOffset_ms = 0;
int pieceIndex = 0;

// constructor
MetalDetectorArray::MetalDetectorArray(int count)
{
    _count = count;
    _enabled = new bool[count];
    for (int i = 0; i < count; i++)
    {
        _enabled[i] = true;
    }
}

// destructor
MetalDetectorArray::~MetalDetectorArray()
{
    if (_enabled != nullptr)
    {
        delete[] _enabled;
    }
}

// get amount of sensors
int MetalDetectorArray::getCount()
{
    return _count;
}

// here for compatibility
void MetalDetectorArray::setSensor(int index, int pin)
{
    return;
}

// calculate sensor triggers
bool triggered(Position sensorPosition, Piece piece, float verticalPoz)
{
    // fix rotations
    piece.angle.angle_deg = fmod(piece.angle.angle_deg, 180.00f);
    if (piece.angle.angle_deg > 90.00f)
    {
        piece.angle.angle_deg -= 90.00f;
        float temp = piece.length_m;
        piece.length_m = piece.width_m;
        piece.width_m = temp;
    }

    // rotate sensors position around center point of simulated piece
    Position piecePosition = {piece.horizontalOffset_m, verticalPoz};
    Position relativePoint = T(sensorPosition, piecePosition, -piece.angle.sinVal, piece.angle.cosVal);

    // check if triggered
    return (treshold(relativePoint, piece) <= 1);
}

// simulate measurement of a sensor
int MetalDetectorArray::readSensor(int index)
{
    // validate index
    if (index < 0 || index > _count)
    {
        return -1;
    }
    
    // check if disabled or if there are no simulated pieces
    if (!_enabled[index] || pieceCount <= 0)
    {
        return 0;
    }

    // calculate simulated piece position
    float verticalPoz = verticalPieceStart_m - pieces[pieceIndex].speed_m_per_s * (millis() - timeOffset_ms) / 1000;
    // simulate next piece if last one passed
    if (verticalPoz < verticalPieceEnd_m || pieces[pieceIndex].speed_m_per_s <= 0)
    {
        pieceIndex = (pieceIndex+1)%pieceCount;
        timeOffset_ms = millis();
    }

    //check if triggered
    if (triggered(sensorPositions[index], pieces[pieceIndex], verticalPoz))
    {
        return 1023;
    }
    else
    {
        return 0;
    }
}

// here for compatibility
void MetalDetectorArray::setThreshold(int index, int threshold)
{
    return;
}

// here for compatibility
int MetalDetectorArray::getThreshold(int index)
{
    if (index >= 0 && index < _count)
    {
        return 511;
    }
    return -1;
}

// enable/disable a sensor
void MetalDetectorArray::setEnabled(int index, bool enabled)
{
    if (index >= 0 && index < _count)
    {
        _enabled[index] = enabled;
    }
}