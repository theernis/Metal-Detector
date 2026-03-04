#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H

#include <thread>
#include <queue>

#include "ProcessPiece.h"

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS));
// process handling
void processHandler(Piece piece, bool* enabled);
// cleanup after process handling
void cleanupHandler();

#endif