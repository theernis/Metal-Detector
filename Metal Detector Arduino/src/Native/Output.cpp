#include <Output.h>

#define OUTPUT_PIECE
//#define OUTPUT_MEASURE_DATA
#define OUTPUT_MEASUREMENT

std::ofstream outputFile;

// ignore output (for performance testing)
void ignoreOutput(SimulationData* data)
{
    return;
}

// print Piece to console (for debugging)
void printPiece(Piece* piece)
{
    std::cout << "speed: " << piece->speed_m_per_s << std::endl;
    std::cout << "length: " << piece->length_m << std::endl;
    std::cout << "width: " << piece->width_m << std::endl;
    std::cout << "angle: " << piece->angle.angle_deg << std::endl;
    std::cout << "horizontal offset: " << piece->horizontalOffset_m << std::endl;
}

// print MeasureData to console (for debugging)
void printMeasureData(MeasureData* data)
{
    for (int i = 0; i < 6; i++)
    {
        std::cout << "sensor i: " << i << std::endl;
        std::cout << "enter time: " << data->sensorData[i].enterTime_s << std::endl;
        std::cout << "exit time: " << data->sensorData[i].exitTime_s << std::endl;
        std::cout << "has entered: " << data->sensorData[i].hasEntered << std::endl;
        std::cout << "has exited: " << data->sensorData[i].hasExited << std::endl;
    }
}

// print Measurement to console (for debugging)
void printMeasurement(Measurement* measurement)
{
    std::cout << "speed: " << measurement->speed_m_per_s << std::endl;
    std::cout << "length: " << measurement->length_m << std::endl;
    std::cout << "width: " << measurement->width_m << std::endl;
    std::cout << "angle: " << measurement->angle_deg << std::endl;
}

// print output to console (for debugging)
void printOutput(SimulationData* data)
{
    #ifdef OUTPUT_PIECE
    printPiece(&data->piece);
    #endif
    #ifdef OUTPUT_MEASURE_DATA
    printMeasureData(data->measureData);
    #endif
    #ifdef OUTPUT_MEASUREMENT
    if (validateMeasurements(data->measureData))
    {
        printMeasurement(&data->measurement);
    }
    else
    {
        std::cout << "insufficient measurements" << std::endl;
    }
    #endif
    std::cout << std::endl;
}

// create parser file for output (for data collection)
void createParserFile(const std::filesystem::path &filepath)
{
    std::filesystem::path parserPath = filepath;
    parserPath += ".parser";
    std::ofstream parserFile(parserPath.string());
    if (!parserFile)
    {
        std::cerr << "Failed to open parser file '" << parserPath << "'\n";
        return;
    }
    #ifdef OUTPUT_PIECE
    parserFile << "Piece_speed_m_per_s:float:" << sizeof(float) << std::endl;
    parserFile << "Piece_length_m:float:" << sizeof(float) << std::endl;
    parserFile << "Piece_width_m:float:" << sizeof(float) << std::endl;
    parserFile << "Piece_angle_deg:float:" << sizeof(float) << std::endl;
    parserFile << "Piece_horizontalOffset_m:float:" << sizeof(float) << std::endl;
    #endif
    #ifdef OUTPUT_MEASURE_DATA
    for (int i = 0; i < 6; i++)
    {
        parserFile << "MeasureData_sensorData_" << i << "_enterTime_s:float:" << sizeof(float) << std::endl;
        parserFile << "MeasureData_sensorData_" << i << "_exitTime_s:float:" << sizeof(float) << std::endl;
        parserFile << "MeasureData_sensorData_" << i << "_hasEntered:bool:" << sizeof(bool) << std::endl;
        parserFile << "MeasureData_sensorData_" << i << "_hasExited:bool:" << sizeof(bool) << std::endl;
    }
    #endif
    #ifdef OUTPUT_MEASUREMENT
    parserFile << "Measurement_speed_m_per_s:float:" << sizeof(float) << std::endl;
    parserFile << "Measurement_length_m:float:" << sizeof(float) << std::endl;
    parserFile << "Measurement_width_m:float:" << sizeof(float) << std::endl;
    parserFile << "Measurement_angle_deg:float:" << sizeof(float) << std::endl;
    #endif
    parserFile.close();
}

// sanitize string for use in filename (replace ':' and ' ' with '_')
static std::string sanitizeString(const std::string &input)
{
    std::string result = input;
    for (char &c : result)
    {
        if (c == ':' || c == ' ')
        {
            c = '_';
        }
    }
    return result;
}

// open output file (for data collection)
void openOutputFile(const std::filesystem::path &filepath)
{
    if (outputFile.is_open())
    {
        return;
    }

    // sanitize only the final component (the name produced by getFilename())
    std::filesystem::path original = filepath;
    std::string name = original.filename().string();
    name = sanitizeString(name);

    std::filesystem::path sanitized = original.parent_path() / name;

    std::filesystem::path dataPath = sanitized;
    dataPath += ".data";
    // open in binary mode so we can write raw floats/booleans
    outputFile.open(dataPath.string(), std::ios::binary);
    if (!outputFile)
    {
        std::cerr << "Failed to open output file '" << dataPath << "'\n";
        // give up early, don't try to write parser file either
        return;
    }

    createParserFile(sanitized);
}

// close output file (for data collection)
void closeOutputFile()
{
    outputFile.close();
}

// write output to file (for data collection)
void writePieceToFile(Piece* piece)
{
    outputFile.write(reinterpret_cast<const char*>(&piece->speed_m_per_s), sizeof(float));
    outputFile.write(reinterpret_cast<const char*>(&piece->length_m), sizeof(float));
    outputFile.write(reinterpret_cast<const char*>(&piece->width_m), sizeof(float));
    outputFile.write(reinterpret_cast<const char*>(&piece->angle.angle_deg), sizeof(float));
    outputFile.write(reinterpret_cast<const char*>(&piece->horizontalOffset_m), sizeof(float));
}

// write output to file (for data collection)
void writeMeasureDataToFile(MeasureData* data)
{
    for (int i = 0; i < 6; ++i)
    {
        outputFile.write(reinterpret_cast<const char*>(&data->sensorData[i].enterTime_s), sizeof(float));
        outputFile.write(reinterpret_cast<const char*>(&data->sensorData[i].exitTime_s), sizeof(float));
        outputFile.write(reinterpret_cast<const char*>(&data->sensorData[i].hasEntered), sizeof(bool));
        outputFile.write(reinterpret_cast<const char*>(&data->sensorData[i].hasExited), sizeof(bool));
    }
}

// write output to file (for data collection)
void writeMeasurementToFile(Measurement* measurement)
{
    outputFile.write(reinterpret_cast<const char*>(&measurement->speed_m_per_s), sizeof(float));
    outputFile.write(reinterpret_cast<const char*>(&measurement->length_m), sizeof(float));
    outputFile.write(reinterpret_cast<const char*>(&measurement->width_m), sizeof(float));
    outputFile.write(reinterpret_cast<const char*>(&measurement->angle_deg), sizeof(float));
}

// write output to file (for data collection)
void writeOutputToFile(SimulationData* data)
{
    if (!outputFile.is_open())
    {
        return;
    }
    #ifdef OUTPUT_PIECE
    writePieceToFile(&data->piece);
    #endif
    #ifdef OUTPUT_MEASURE_DATA
    writeMeasureDataToFile(data->measureData);
    #endif
    #ifdef OUTPUT_MEASUREMENT
    writeMeasurementToFile(&data->measurement);
    #endif
}