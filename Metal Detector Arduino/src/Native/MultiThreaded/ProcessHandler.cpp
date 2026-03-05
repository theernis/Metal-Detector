#include "ProcessHandler.h"

#include <thread>
#include <queue>

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

// thread function to process output data and free thread data
void outputThread(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    #ifdef PRINT_THREAD_ID
    std::cout << "Output thread ID: " << std::this_thread::get_id() << std::endl;
    #endif
    #ifdef PRINT_THREAD_NUMBER
    std::cout << "Output thread number: " << ++outputThreadCounter << std::endl;
    #endif
    // process output data
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

// worker thread function to process a piece and store the result in the thread data
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

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

std::thread* outputThreadHandle;
int threadCount;

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    outputFunction = processOutput;

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

    outputThreadHandle = new std::thread(outputThread, outputFunction);
    threadCount = std::thread::hardware_concurrency();
    return;
}

// process handling
void processHandler(Piece piece, bool* enabled)
{
    // if queue is full, wait for output thread to process some pieces
    if (threadQueue.size() >= threadCount)
    {
        outputThreadHandle->join();
        delete outputThreadHandle;
        outputThreadHandle = new std::thread(outputThread, outputFunction);
    }
    // create new thread
    SimulationData* data = new SimulationData;
    std::thread* thread = new std::thread(workerThread, piece, enabled, data);
    ThreadData* threadData = new ThreadData{thread, data};
    threadQueue.push(threadData);
}

// cleanup after process handling
void cleanupHandler()
{
    // wait for all threads to finish
    outputThreadHandle->join();
    // clean up
    delete outputThreadHandle;
    return;
}