#include "ProcessHandler.h"

#include <thread>

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

bool* _enabled;

struct ThreadData
{
    std::thread* thread;
    SimulationData* data;
};

ThreadData* threadArray;
unsigned int threadArraySize;
unsigned int threadArrayIndex;

// thread function to process output data and free thread data
void outputThread()
{
    for (int i = 0; i < threadArrayIndex; i++)
    {
        if (threadArray[i].thread->joinable())
        {
            threadArray[i].thread->join();
        }
        outputFunction(threadArray[i].data);
        delete threadArray[i].thread;
        delete threadArray[i].data;
    }
    threadArrayIndex = 0;

    return;
}

// worker thread function to process a piece and store the result in the thread data
void workerThread(Piece piece, SimulationData* data)
{
    processPiece(piece, _enabled, data);

    return;
}

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS), bool* enabled)
{
    _enabled = enabled;
    outputFunction = processOutput;

    // initialize lookup tables
    fastSinDeg(0);
    fastCosDeg(0);
    fastTanDeg(0);

    threadArraySize = std::thread::hardware_concurrency();
    threadArrayIndex = 0;
    threadArray = new ThreadData[threadArraySize];

    return;
}

// process handling
void processHandler(Piece piece)
{
    if (threadArrayIndex >= threadArraySize)
    {
        outputThread();
    }
    SimulationData* data = new SimulationData;
    std::thread* thread = new std::thread(workerThread, piece, data);
    threadArray[threadArrayIndex] = (ThreadData){thread, data};
    threadArrayIndex++;
    return;
}

// cleanup after process handling
void cleanupHandler()
{
    // clean up
    outputThread();
    delete threadArray;
    return;
}