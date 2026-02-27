#include <iostream>
#include <ctime>
#include <string>
#include <filesystem> // directory handling for desktop output
#include <cstdlib>    // getenv

#include "Process.h"

using namespace std;

#define TEST

enum OutputMode {
    IGNORE,
    PRINT,
    WRITE
};

// helper to ensure Desktop/Simulations exists and return its path
static std::filesystem::path getFilename() {
    namespace fs = std::filesystem;
    const char *userProfile = std::getenv("USERPROFILE");
    fs::path base = userProfile ? fs::path(userProfile) : fs::current_path();
    fs::path dir = base / "Desktop" / "Simulations";
    fs::create_directories(dir);
    time_t startTime;
    time(&startTime);
    std::string baseName = ctime(&startTime);
    if (!baseName.empty() && baseName.back() == '\n')
    {
        baseName.pop_back();
    }
    std::filesystem::path fullPath = dir / baseName;
    return fullPath;
}

int main() {
    void (*outputFunction)(OUTPUT_FUNCTION_ARGS);
    OutputMode outputMode = WRITE;
    switch (outputMode)
    {
    case IGNORE:
        outputFunction = ignoreOutput;
        break;
    case PRINT:
        outputFunction = printOutput;
        break;
    case WRITE:
        openOutputFile(getFilename());
        outputFunction = writeOutputToFile;
        break;
    default:
        outputFunction = ignoreOutput;
        break;
    }
    #ifndef TEST
    bool enabled[] = {true, true, true, true, true, true};
    PieceRange pieceRange;
    pieceRange.speed = createRange(0.01f, 0.5f, 0.01f);
    pieceRange.length = createRange(0.01f, 0.5f, 0.01f);
    pieceRange.width = createRange(0.01f, 0.5f, 0.01f);
    pieceRange.angle = createRange(-44.0f, 45.0f, 1.0f);
    pieceRange.horizontalOffset = createRange(-0.16f, 0.16f, 0.01f);
    processPieceRanges(pieceRange, enabled, outputFunction);
    #else
    test(outputFunction);
    #endif
    
    if (outputMode == WRITE) {
        closeOutputFile();
    }

    missCount();
    
    return 0;
}