#include "ProcessHandler.h"

#include <thread>
#include <chrono>

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

bool* _enabled;

struct Job
{
    Piece* piece = nullptr; // input
    SimulationData* data = nullptr; // output
};

bool working = false;

unsigned int workerThreadCount;
const unsigned int jobBufferSize = 1024;

std::thread** workerThreads;
Job** jobBuffers;

std::thread* outputHandler;

// thread function to process output data and free thread data
void outputThread()
{
    int threadIndex = 0;
    int jobIndex = 0;
    while (working || (jobBuffers[threadIndex][jobIndex].piece != nullptr || jobBuffers[threadIndex][jobIndex].data != nullptr))
    {
        while (jobBuffers[threadIndex][jobIndex].piece == nullptr || jobBuffers[threadIndex][jobIndex].data == nullptr)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        outputFunction(jobBuffers[threadIndex][jobIndex].data);

        delete jobBuffers[threadIndex][jobIndex].piece;
        jobBuffers[threadIndex][jobIndex].piece = nullptr;
        delete jobBuffers[threadIndex][jobIndex].data;
        jobBuffers[threadIndex][jobIndex].data = nullptr;

        threadIndex++;
        if (threadIndex >= workerThreadCount)
        {
            threadIndex = 0;
            jobIndex++;
            if (jobIndex >= jobBufferSize)
            {
                jobIndex = 0;
            }
        }
    }

    return;
}

// worker thread function to process a piece and store the result in the thread data
void workerThread(Job* jobBuffer)
{
    int jobIndex = 0;
    while (working || jobBuffer[jobIndex].piece != nullptr)
    {
        while (jobBuffer[jobIndex].piece == nullptr || jobBuffer[jobIndex].data != nullptr)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        jobBuffer[jobIndex].data = new SimulationData;
        processPiece(*jobBuffer[jobIndex].piece, _enabled, jobBuffer[jobIndex].data);
    }
    
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

    workerThreadCount = std::thread::hardware_concurrency() - 2;
    jobBuffers = new Job*[workerThreadCount];
    for (int i = 0; i < workerThreadCount; i++)
    {
        jobBuffers[i] = new Job[jobBufferSize];
    }
    working = true;
    workerThreads = new std::thread*[workerThreadCount];
    for (int i = 0; i < workerThreadCount; i++)
    {
        workerThreads[i] = new std::thread(workerThread, jobBuffers[i]);
    }
    
    outputHandler = new std::thread(outputThread);

    return;
}

// process handling
void processHandler(Piece piece)
{
    static int threadIndex = 0;
    static int jobIndex = 0;
    while (jobBuffers[threadIndex][jobIndex].piece != nullptr || jobBuffers[threadIndex][jobIndex].data != nullptr)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    Piece* temp = new Piece;
    *temp = piece;
    threadIndex++;
    if (threadIndex >= workerThreadCount)
    {
        threadIndex = 0;
        jobIndex++;
        if (jobIndex >= jobBufferSize)
        {
            jobIndex = 0;
        }
    }
    
    return;
}

// cleanup after process handling
void cleanupHandler()
{
    // clean up
    outputHandler->join();
    delete outputHandler;
    for (int i = 0; i < workerThreadCount; i++)
    {
        workerThreads[i]->join();
        delete workerThreads[i];
    }
    delete workerThreads;
    for (int i = 0; i < workerThreadCount; i++)
    {
        delete jobBuffers[i];
    }
    delete jobBuffers;
    return;
}