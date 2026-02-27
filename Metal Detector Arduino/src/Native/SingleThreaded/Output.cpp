#include <Output.h>

using namespace std;

#define OUTPUT_PIECE
//#define OUTPUT_MEASURE_DATA
#define OUTPUT_MEASUREMENT

ofstream outputFile;

void ignoreOutput(SimulationData* data) {
    return;
}

void printPiece(Piece* piece) {
    cout << "speed: " << (*piece).speed_m_per_s << endl;
    cout << "length: " << (*piece).length_m << endl;
    cout << "width: " << (*piece).width_m << endl;
    cout << "angle: " << (*piece).angle.angle_deg << endl;
    cout << "horizontal offset: " << (*piece).horizontalOffset_m << endl;
}

void printMeasureData(MeasureData* data) {
    for (int i = 0; i < 6; i++)
    {
        cout << "sensor i: " << i << endl;
        cout << "enter time: " << (*data).sensorData[i].enterTime_s << endl;
        cout << "exit time: " << (*data).sensorData[i].exitTime_s << endl;
        cout << "has entered: " << (*data).sensorData[i].hasEntered << endl;
        cout << "has exited: " << (*data).sensorData[i].hasExited << endl;
    }
}

void printMeasurement(Measurement* measurement) {
        cout << "speed: " << (*measurement).speed_m_per_s << endl;
        cout << "length: " << (*measurement).length_m << endl;
        cout << "width: " << (*measurement).width_m << endl;
        cout << "angle: " << (*measurement).angle_deg << endl;
}

void printOutput(SimulationData* data) {
    #ifdef OUTPUT_PIECE
    printPiece(&(*data).piece);
    #endif
    #ifdef OUTPUT_MEASURE_DATA
    printMeasureData(&(*data).measureData);
    #endif
    #ifdef OUTPUT_MEASUREMENT
    if (validateMeasurements(&(*data).measureData))
    {
        printMeasurement(&(*data).measurement);
    }
    else
    {
        cout << "insufficient measurements" << endl;
    }
    #endif
    cout << endl;
}

void createParserFile(const std::filesystem::path &filepath) {
    std::filesystem::path parserPath = filepath;
    parserPath += ".parser";
    ofstream parserFile(parserPath.string());
    if (!parserFile) {
        std::cerr << "Failed to open parser file '" << parserPath << "'\n";
        return;
    }
    #ifdef OUTPUT_PIECE
    parserFile << "Piece_speed_m_per_s:float:" << sizeof(float) << endl;
    parserFile << "Piece_length_m:float:" << sizeof(float) << endl;
    parserFile << "Piece_width_m:float:" << sizeof(float) << endl;
    parserFile << "Piece_angle_deg:float:" << sizeof(float) << endl;
    parserFile << "Piece_horizontalOffset_m:float:" << sizeof(float) << endl;
    #endif
    #ifdef OUTPUT_MEASURE_DATA
    for (int i = 0; i < 6; i++)
    {
        parserFile << "MeasureData_sensorData_" << i << "_enterTime_s:float:" << sizeof(float) << endl;
        parserFile << "MeasureData_sensorData_" << i << "_exitTime_s:float:" << sizeof(float) << endl;
        parserFile << "MeasureData_sensorData_" << i << "_hasEntered:bool:" << sizeof(bool) << endl;
        parserFile << "MeasureData_sensorData_" << i << "_hasExited:bool:" << sizeof(bool) << endl;
    }
    #endif
    #ifdef OUTPUT_MEASUREMENT
    parserFile << "Measurement_speed_m_per_s:float:" << sizeof(float) << endl;
    parserFile << "Measurement_length_m:float:" << sizeof(float) << endl;
    parserFile << "Measurement_width_m:float:" << sizeof(float) << endl;
    parserFile << "Measurement_angle_deg:float:" << sizeof(float) << endl;
    #endif
    parserFile.close();
}

static std::string sanitizeString(const std::string &input) {
    std::string result = input;
    for (char &c : result) {
        if (c == ':' || c == ' ') {
            c = '_';
        }
    }
    return result;
}

void openOutputFile(const std::filesystem::path &filepath) {
    if (outputFile.is_open()) {
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
    if (!outputFile) {
        std::cerr << "Failed to open output file '" << dataPath << "'\n";
        // give up early, don't try to write parser file either
        return;
    }

    createParserFile(sanitized);
}

void closeOutputFile() {
    outputFile.close();
}

void writePieceToFile(Piece* piece) {
    if (!outputFile.is_open()) {
        return;
    }
    outputFile.write(reinterpret_cast<const char*>(&(*piece).speed_m_per_s), sizeof((*piece).speed_m_per_s));
    outputFile.write(reinterpret_cast<const char*>(&(*piece).length_m), sizeof((*piece).length_m));
    outputFile.write(reinterpret_cast<const char*>(&(*piece).width_m), sizeof((*piece).width_m));
    outputFile.write(reinterpret_cast<const char*>(&(*piece).angle.angle_deg), sizeof((*piece).angle.angle_deg));
    outputFile.write(reinterpret_cast<const char*>(&(*piece).horizontalOffset_m), sizeof((*piece).horizontalOffset_m));
}

void writeMeasureDataToFile(MeasureData* data) {
    for (int i = 0; i < 6; ++i) {
        outputFile.write(reinterpret_cast<const char*>(&(*data).sensorData[i].enterTime_s), sizeof((*data).sensorData[i].enterTime_s));
        outputFile.write(reinterpret_cast<const char*>(&(*data).sensorData[i].exitTime_s), sizeof((*data).sensorData[i].exitTime_s));
        outputFile.write(reinterpret_cast<const char*>(&(*data).sensorData[i].hasEntered), sizeof((*data).sensorData[i].hasEntered));
        outputFile.write(reinterpret_cast<const char*>(&(*data).sensorData[i].hasExited), sizeof((*data).sensorData[i].hasExited));
    }
}

void writeMeasurementToFile(Measurement* measurement) {
    outputFile.write(reinterpret_cast<const char*>(&(*measurement).speed_m_per_s), sizeof((*measurement).speed_m_per_s));
    outputFile.write(reinterpret_cast<const char*>(&(*measurement).length_m), sizeof((*measurement).length_m));
    outputFile.write(reinterpret_cast<const char*>(&(*measurement).width_m), sizeof((*measurement).width_m));
    outputFile.write(reinterpret_cast<const char*>(&(*measurement).angle_deg), sizeof((*measurement).angle_deg));
}


void writeOutputToFile(SimulationData* data) {
    #ifdef OUTPUT_PIECE
    writePieceToFile(&(*data).piece);
    #endif
    #ifdef OUTPUT_MEASURE_DATA
    writeMeasureDataToFile(&(*data).measureData);
    #endif
    #ifdef OUTPUT_MEASUREMENT
    writeMeasurementToFile(&(*data).measurement);
    #endif
}