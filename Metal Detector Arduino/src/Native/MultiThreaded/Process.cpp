#include "Process.h"

//#define PRINT_THREAD_ID
#define PRINT_THREAD_NUMBER

#ifdef PRINT_THREAD_NUMBER
int mainThreadCounter = 0;
int outputThreadCounter = 0;
int workerThreadCounter = 0;
#endif

struct ThreadData
{
    std::thread* thread;
    SimulationData* data;
};

std::queue<ThreadData*> threadQueue;

void outputThread(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    #ifdef PRINT_THREAD_ID
    std::cout << "Output thread ID: " << std::this_thread::get_id() << std::endl;
    #endif
    #ifdef PRINT_THREAD_NUMBER
    std::cout << "Output thread number: " << ++outputThreadCounter << std::endl;
    #endif
    while (!threadQueue.empty())
    {
        ThreadData* threadData = threadQueue.front();
        threadQueue.pop();
        if (threadData->thread->joinable())
        {
            threadData->thread->join();
        }
        processOutput(threadData->data);
        delete threadData->thread;
        delete threadData->data;
        delete threadData;
    }
}

void workerThread(Piece piece, bool* enabled, SimulationData* data)
{
    #ifdef PRINT_THREAD_ID
    std::cout << "Worker thread ID: " << std::this_thread::get_id() << std::endl;
    #endif
    #ifdef PRINT_THREAD_NUMBER
    std::cout << "Worker thread number: " << ++workerThreadCounter << std::endl;
    #endif
    processPiece(piece, enabled, data);
}

void processPieceRanges(PieceRange pieceRange, bool* enabled, void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    // initialize lookup tables
    fastSinDeg(0);
    fastCosDeg(0);
    fastTanDeg(0);

    #ifdef PRINT_THREAD_ID
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;
    #endif
    #ifdef PRINT_THREAD_NUMBER
    std::cout << "Main thread number: " << ++mainThreadCounter << std::endl;
    #endif
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
    
    std::thread* outputThreadHandle = new std::thread(outputThread, processOutput);
    int threadCount = std::thread::hardware_concurrency();
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
                        if (threadQueue.size() >= threadCount)
                        {
                            outputThreadHandle->join();
                            delete outputThreadHandle;
                            outputThreadHandle = new std::thread(outputThread, processOutput);
                        }
                        SimulationData* data = new SimulationData;
                        std::thread* thread = new std::thread(workerThread, (Piece){speedValues[speed], lengthValues[length], widthValues[width], angleDeg(angleValues[angle]), horizontalOffsetValues[horizontalOffset]}, enabled, data);
                        ThreadData* threadData = new ThreadData{thread, data};
                        threadQueue.push(threadData);
                    }
                }
            }
        }
    }

    outputThreadHandle->join();
    delete outputThreadHandle;
    delete[] speedValues;
    delete[] lengthValues;
    delete[] widthValues;
    delete[] angleValues;
    delete[] horizontalOffsetValues;
}