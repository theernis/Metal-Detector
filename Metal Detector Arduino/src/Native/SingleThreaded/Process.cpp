#include "Process.h"

// processes all pieces in the given piece range and calls the processOutput callback for each piece
void processPieceRanges(PieceRange pieceRange, bool* enabled, void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    // initialize lookup tables
    float* speedValues = new float[pieceRange.speed.stepCount + 1];
    float* lengthValues = new float[pieceRange.length.stepCount + 1];
    float* widthValues = new float[pieceRange.width.stepCount + 1];
    float* angleValues = new float[pieceRange.angle.stepCount + 1];
    float* horizontalOffsetValues = new float[pieceRange.horizontalOffset.stepCount + 1];
    for (int speed = 0; speed <= pieceRange.speed.stepCount; speed++)
    {
        speedValues[speed] = getRangeValue(pieceRange.speed, speed);
    }
    for (int length = 0; length <= pieceRange.length.stepCount; length++)
    {
        lengthValues[length] = getRangeValue(pieceRange.length, length);
    }
    for (int width = 0; width <= pieceRange.width.stepCount; width++)
    {
        widthValues[width] = getRangeValue(pieceRange.width, width);
    }
    for (int angle = 0; angle <= pieceRange.angle.stepCount; angle++)
    {
        angleValues[angle] = getRangeValue(pieceRange.angle, angle);
    }
    for (int horizontalOffset = 0; horizontalOffset <= pieceRange.horizontalOffset.stepCount; horizontalOffset++)
    {
        horizontalOffsetValues[horizontalOffset] = getRangeValue(pieceRange.horizontalOffset, horizontalOffset);
    }

    // process pieces
    for (int speed = 0; speed <= pieceRange.speed.stepCount; speed++)
    {
        for (int length = 0; length <= pieceRange.length.stepCount; length++)
        {
            for (int width = 0; width <= pieceRange.width.stepCount; width++)
            {
                for (int angle = 0; angle <= pieceRange.angle.stepCount; angle++)
                {
                    for (int horizontalOffset = 0; horizontalOffset <= pieceRange.horizontalOffset.stepCount; horizontalOffset++)
                    {
                        // process piece and call output callback
                        SimulationData data;
                        processPiece((Piece){speedValues[speed], lengthValues[length], widthValues[width], angleDeg(angleValues[angle]), horizontalOffsetValues[horizontalOffset]}, enabled, &data);
                        processOutput(&data);
                    }
                }
            }
        }
    }
}