#ifndef OUTPUT_H
#define OUTPUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "SimulationData.h"
#include "CalculateMeasureData.h"
#include "MeasurementCalculations.h"

#define OUTPUT_FUNCTION_ARGS SimulationData*

struct SimulationData
{
    Piece piece;
    MeasureData measureData;
    Measurement measurement;
};

void ignoreOutput(SimulationData* data);
void printOutput(SimulationData* data);

// filepath is allowed so callers can pass the result of getFilename()
void openOutputFile(const std::filesystem::path &filepath);
void closeOutputFile();
void writeOutputToFile(SimulationData* data);

#endif