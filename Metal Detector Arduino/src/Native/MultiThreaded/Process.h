#ifndef PROCESS_H
#define PROCESS_H

#include <thread>
#include <queue>

#include "ProcessPiece.h"

void processPieceRanges(PieceRange pieceRange, bool* enabled, void (*processOutput)(SimulationData*));

#endif