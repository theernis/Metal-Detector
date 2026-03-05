#ifndef PROCESSHANDLER_H
#define PROCESSHANDLER_H

#include "ProcessPiece.h"

// initialize process handling
void initializeHandler(void (*processOutput)(OUTPUT_FUNCTION_ARGS), bool* enabled);
// process handling
void processHandler(Piece piece);
// cleanup after process handling
void cleanupHandler();

#endif