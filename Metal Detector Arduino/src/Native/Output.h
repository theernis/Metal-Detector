#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "SimulationData.h"
#include "CalculateMeasureData.h"
#include "MeasurementCalculations.h"

// made this a macro so it can be used in function pointer declarations
#define OUTPUT_FUNCTION_ARGS SimulationData*

// structure for output data
struct SimulationData
{
    Piece piece;
    MeasureData measureData;
    Measurement measurement;
};

// ignore output (for performance testing)
void ignoreOutput(SimulationData* data);
// print output to console (for debugging)
void printOutput(SimulationData* data);
// open output file (for data collection)
void openOutputFile(const std::filesystem::path &filepath);
// close output file (for data collection)
void closeOutputFile();
// write output to file (for data collection)
void writeOutputToFile(SimulationData* data);

#endif