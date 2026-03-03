#include "Serial.h"

// check data integrity
bool checkSerialDataIntegrity(u_int8_t* data, int packetSize)
{
    int dataSize = packetSize-2;
    u_int8_t sum = dataSize;
    u_int8_t parity = dataSize;
    for (int i = 0; i < dataSize; i++)
    {
        // calculate sum
        sum += data[i];
        // calculate XOR
        parity ^= data[i];
    }
    return (sum == data[packetSize-2] && parity == data[packetSize-1]);
}

// read serial data
void readSerialData(void (*handler)(u_int8_t*, int))
{
    static bool reading = false;
    static u_int8_t* buffer = nullptr;
    static int bufferSize = 0;
    static int bytesRead = 0;
    // read data if available, 5 packets in one go at most
    int counter = 0;
    while (Serial.available() > 0 && counter < 5)
    {
        // look for start byte
        if (!reading && Serial.read() == 0xFF)
        {
            reading = true;
            bufferSize = Serial.read() + 2; // size including checksum and parity
            buffer = new u_int8_t[bufferSize];
            bytesRead = 0;
        }
        // read data if start byte was found
        else if (reading)
        {
            // read data to buffer
            buffer[bytesRead] = Serial.read();
            bytesRead++;
            // if buffer is filled
            if (bytesRead >= bufferSize)
            {
                // check integrity
                if (checkSerialDataIntegrity(buffer, bufferSize))
                {
                    // handle data received
                    handler(buffer, bufferSize);
                }
                delete[] buffer;
                buffer = nullptr;
                reading = false;
                counter++;
                return;
            }
        }
    }
}

// send serial data
void sendDataOverSerial(u_int8_t* data, int dataSize)
{
    u_int8_t signalSize = 2 + dataSize + 2;
    u_int8_t* signal = new u_int8_t[signalSize];
    u_int8_t sum = dataSize;
    u_int8_t parity = dataSize;

    // start byte
    signal[0] = 0xFF;
    // size byte
    signal[1] = dataSize;
    // data bytes + sum and parity calculations
    for (int i = 0; i < dataSize; i++)
    {
        signal[2 + i] = data[i];
        sum += data[i];
        parity ^= data[i];
    }
    // sum byte
    signal[dataSize + 2] = sum;
    // parity byte
    signal[dataSize + 3] = parity;
    // send data trough serial
    Serial.write(signal, signalSize);

    delete[] signal;
}