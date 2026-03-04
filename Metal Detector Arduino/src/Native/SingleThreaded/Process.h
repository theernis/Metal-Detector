#ifndef PROCESS_H
#define PROCESS_H

#include "ProcessPiece.h"

// processes all pieces in the given piece range and calls the processOutput callback for each piece
void processPieceRanges(PieceRange pieceRange, bool* enabled, void (*processOutput)(SimulationData*));

#endif