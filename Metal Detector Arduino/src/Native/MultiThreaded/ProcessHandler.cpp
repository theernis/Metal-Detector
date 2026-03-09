#include "ProcessHandler.h"

#include <thread>
#include <chrono>
#include <iostream>

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

bool* _enabled;

enum HandlerThread {MAIN, WORKER, OUTPUT};

struct Job
{
    Piece* piece = nullptr; // input
    SimulationData* data = nullptr; // output
    HandlerThread handler = MAIN;
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
    while (working || jobBuffers[threadIndex][jobIndex].handler != MAIN)
    {
        if (jobBuffers[threadIndex][jobIndex].handler != OUTPUT)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        else
        {
            outputFunction(jobBuffers[threadIndex][jobIndex].data);

            jobBuffers[threadIndex][jobIndex].handler = MAIN;

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
    }

    return;
}

// worker thread function to process a piece and store the result in the thread data
void workerThread(Job* jobBuffer)
{
    int jobIndex = 0;
    while (working || jobBuffer[jobIndex].handler == WORKER)
    {
        if (jobBuffer[jobIndex].handler != WORKER)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (!working)
            {
                return;
            }
            
        }
        else
        {
            processPiece(*jobBuffer[jobIndex].piece, _enabled, jobBuffer[jobIndex].data);
            jobBuffer[jobIndex].handler = OUTPUT;

            jobIndex++;
            if (jobIndex >= jobBufferSize)
            {
                jobIndex = 0;
            }
        }
    }
    
    return;
}

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS), bool* enabled)
{
    _enabled = enabled;
    outputFunction = processOutput;

    workerThreadCount = std::thread::hardware_concurrency() - 2;
    jobBuffers = new Job*[workerThreadCount];
    for (int i = 0; i < workerThreadCount; i++)
    {
        jobBuffers[i] = new Job[jobBufferSize];
        for (int j = 0; j < jobBufferSize; j++)
        {
            jobBuffers[i][j].piece = new Piece;
            jobBuffers[i][j].data = new SimulationData;
            jobBuffers[i][j].data->measureData = new MeasureData;
        }
        
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
    while (jobBuffers[threadIndex][jobIndex].handler != MAIN)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    *jobBuffers[threadIndex][jobIndex].piece = piece;
    jobBuffers[threadIndex][jobIndex].handler = WORKER;
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
    working = false;
    // clean up
    for (int i = 0; i < workerThreadCount; i++)
    {
        workerThreads[i]->join();
        delete workerThreads[i];
    }
    outputHandler->join();
    delete outputHandler;
    delete[] workerThreads;
    for (int i = 0; i < workerThreadCount; i++)
    {
        for (int j = 0; j < jobBufferSize; j++)
        {
            cleanupMeasurements(jobBuffers[i][j].data->measureData);
            delete jobBuffers[i][j].data->measureData;
            delete jobBuffers[i][j].data;
            delete jobBuffers[i][j].piece;
        }
        
        delete[] jobBuffers[i];
    }
    delete[] jobBuffers;
    return;
}