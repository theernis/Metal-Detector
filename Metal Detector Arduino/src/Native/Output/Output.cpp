#include <Output.h>

#include <cstring>

bool _printPiece = false;
bool _printMeasureData = false;
bool _printMeasurement = false;

// set desired outputs
void setOutputs(bool printPiece, bool printMeasureData, bool printMeasurement)
{
    _printPiece = printPiece;
    _printMeasureData = printMeasureData;
    _printMeasurement = printMeasurement;
}

std::ofstream outputFile;
const unsigned int outputBufferSize = 1 << 16;
char outputBuffer[outputBufferSize];
unsigned int outputBufferIndex = 0;

void dumpBuffer()
{
    if (outputBufferSize != 0)
    {
        outputFile.write(outputBuffer, outputBufferIndex);
        outputBufferIndex = 0;
    }
}

void writeFloat(float data)
{
    if (outputBufferSize > outputBufferIndex + sizeof(float))
    {
        dumpBuffer();
    }
    memcpy(&outputBuffer[outputBufferIndex], &data, sizeof(float));
    outputBufferIndex += sizeof(float);
}

void writeBool(bool data)
{
    if (outputBufferSize > outputBufferIndex + sizeof(bool))
    {
        dumpBuffer();
    }
    memcpy(&outputBuffer[outputBufferIndex], &data, sizeof(bool));
    outputBufferIndex += sizeof(bool);
}

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
    if (_printPiece)
    {
        printPiece(data->piece);
    }
    if (_printMeasureData)
    {
        printMeasureData(data->measureData);
    }
    if (_printMeasurement)
    {
        if (validateMeasurements(data->measureData))
        {
            printMeasurement(data->measurement);
        }
        else
        {
            std::cout << "insufficient measurements" << std::endl;
        }
    }
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
    if (_printPiece)
    {
        parserFile << "Piece_speed_m_per_s:float:" << sizeof(float) << std::endl;
        parserFile << "Piece_length_m:float:" << sizeof(float) << std::endl;
        parserFile << "Piece_width_m:float:" << sizeof(float) << std::endl;
        parserFile << "Piece_angle_deg:float:" << sizeof(float) << std::endl;
        parserFile << "Piece_horizontalOffset_m:float:" << sizeof(float) << std::endl;
    }
    if (_printMeasureData)
    {
        for (int i = 0; i < 6; i++)
        {
            parserFile << "MeasureData_sensorData_" << i << "_enterTime_s:float:" << sizeof(float) << std::endl;
            parserFile << "MeasureData_sensorData_" << i << "_exitTime_s:float:" << sizeof(float) << std::endl;
            parserFile << "MeasureData_sensorData_" << i << "_hasEntered:bool:" << sizeof(bool) << std::endl;
            parserFile << "MeasureData_sensorData_" << i << "_hasExited:bool:" << sizeof(bool) << std::endl;
        }
    }
    if (_printMeasurement)
    {   
        parserFile << "Measurement_speed_m_per_s:float:" << sizeof(float) << std::endl;
        parserFile << "Measurement_length_m:float:" << sizeof(float) << std::endl;
        parserFile << "Measurement_width_m:float:" << sizeof(float) << std::endl;
        parserFile << "Measurement_angle_deg:float:" << sizeof(float) << std::endl;
    }
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
    dumpBuffer();
    outputFile.close();
}

// write output to file (for data collection)
void writePieceToFile(Piece* piece)
{
    writeFloat(piece->speed_m_per_s);
    writeFloat(piece->length_m);
    writeFloat(piece->width_m);
    writeFloat(piece->angle.angle_deg);
    writeFloat(piece->horizontalOffset_m);
}

// write output to file (for data collection)
void writeMeasureDataToFile(MeasureData* data)
{
    for (int i = 0; i < 6; ++i)
    {
        writeFloat(data->sensorData[i].enterTime_s);
        writeFloat(data->sensorData[i].exitTime_s);
        writeBool(data->sensorData[i].hasEntered);
        writeBool(data->sensorData[i].hasExited);
    }
}

// write output to file (for data collection)
void writeMeasurementToFile(Measurement* measurement)
{
    writeFloat(measurement->speed_m_per_s);
    writeFloat(measurement->length_m);
    writeFloat(measurement->width_m);
    writeFloat(measurement->angle_deg);
}

// write output to file (for data collection)
void writeOutputToFile(SimulationData* data)
{
    if (!outputFile.is_open())
    {
        return;
    }
    if (_printPiece)
    {
        writePieceToFile(data->piece);
    }
    if (_printMeasureData)
    {
        writeMeasureDataToFile(data->measureData);
    }
    if (_printMeasurement)
    {
        writeMeasurementToFile(data->measurement);
    }
}