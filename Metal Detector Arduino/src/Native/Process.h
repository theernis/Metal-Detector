#ifndef PROCESS_H
#define PROCESS_H

#include "ProcessHandler.h"

// processes all pieces in the given piece range and calls the processOutput callback for each piece
void processPieceRanges(PieceRange pieceRange, bool* enabled, void (*processOutput)(OUTPUT_FUNCTION_ARGS));

// test function to process all pieces from SimulationData and output results
void test(bool* enabled, void (*processOutput)(OUTPUT_FUNCTION_ARGS));

#endif