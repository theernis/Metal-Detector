#include "Process.h"

struct ThreadData {
    std::thread* thread;
    SimulationData* data;
};

std::queue<ThreadData*> threadQueue;

void outputThread(bool* working, void (*processOutput)(OUTPUT_FUNCTION_ARGS)) {
    while (*working || !threadQueue.empty()) {
        if (!threadQueue.empty()) {
            ThreadData* threadData = threadQueue.front();
            threadQueue.pop();
            (*threadData).thread->join();
            processOutput((*threadData).data);
            delete (*threadData).thread;
            delete (*threadData).data;
            delete threadData;
        }
    }
}

void workerThread(Piece piece, bool* enabled, SimulationData* data) {
    *data = processPiece(piece, enabled);
}

void processPieceRanges(PieceRange pieceRange, bool* enabled, void (*processOutput)(OUTPUT_FUNCTION_ARGS)) {
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
    
    bool working = true;
    std::thread outputThreadHandle(outputThread, &working, processOutput);
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
                        SimulationData* data = new SimulationData;
                        std::thread* thread = new std::thread(workerThread, (Piece){speedValues[speed], lengthValues[length], widthValues[width], angleDeg(angleValues[angle]), horizontalOffsetValues[horizontalOffset]}, enabled, data);
                        ThreadData* threadData = new ThreadData{thread, data};
                        threadQueue.push(threadData);
                    }
                }
            }
        }
    }

    working = false;
    outputThreadHandle.join();
    delete[] speedValues;
    delete[] lengthValues;
    delete[] widthValues;
    delete[] angleValues;
    delete[] horizontalOffsetValues;
}