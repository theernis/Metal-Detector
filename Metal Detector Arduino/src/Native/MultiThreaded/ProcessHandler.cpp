#include "ProcessHandler.h"

#include <thread>

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

ThreadData* threadArray;
unsigned int threadArraySize;
unsigned int threadArrayIndex;

// thread function to process output data and free thread data
void outputThread(void (*processOutput)(OUTPUT_FUNCTION_ARGS))
{
    #ifdef PRINT_THREAD_ID
    std::cout << "Output thread ID: " << std::this_thread::get_id() << std::endl;
    #endif
    #ifdef PRINT_THREAD_NUMBER
    std::cout << "Output thread number: " << ++outputThreadCounter << std::endl;
    #endif

    for (int i = 0; i < threadArrayIndex; i++)
    {
        if (threadArray[i].thread->joinable())
        {
            threadArray[i].thread->join();
        }
        processOutput(threadArray[i].data);
        delete threadArray[i].thread;
        delete threadArray[i].data;
    }
    threadArrayIndex = 0;

    return;
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

    return;
}

void (*outputFunction)(OUTPUT_FUNCTION_ARGS);

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

    threadArraySize = std::thread::hardware_concurrency();
    threadArrayIndex = 0;
    threadArray = new ThreadData[threadArraySize];

    return;
}

// process handling
void processHandler(Piece piece, bool* enabled)
{
    if (threadArrayIndex >= threadArraySize)
    {
        std::thread outputThreadHandle(outputThread, outputFunction);
        outputThreadHandle.join();
    }
    SimulationData* data = new SimulationData;
    std::thread* thread = new std::thread(workerThread, piece, enabled, data);
    threadArray[threadArrayIndex] = (ThreadData){thread, data};
    threadArrayIndex++;
    return;
}

// cleanup after process handling
void cleanupHandler()
{
    std::thread outputThreadHandle(outputThread, outputFunction);
    outputThreadHandle.join();
    // clean up
    delete threadArray;
    return;
}