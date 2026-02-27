#ifndef PROCESS_H
#define PROCESS_H

#include "ProcessPiece.h"

void processPieceRanges(PieceRange pieceRange, bool* enabled, void (*processOutput)(SimulationData*));

#endif