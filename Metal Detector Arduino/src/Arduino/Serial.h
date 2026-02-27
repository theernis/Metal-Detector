#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>

bool checkSerialDataIntegrity(u_int8_t* data, int packetSize);
void readSerialData(void (*handler)(u_int8_t*, int));
void sendDataOverSerial(u_int8_t* data, int dataSize);

#endif