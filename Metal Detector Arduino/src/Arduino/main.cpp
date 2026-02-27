#include <Arduino.h>
#include "MetalDetector.h"
#include "Measure.h"
#include "Serial.h"

MetalDetectorArray* sensors = nullptr;
unsigned long sendInterval = 100; // milliseconds
bool sendingData = true;

// process received packets
void processSerialData(u_int8_t* data, int packetSize) {
  u_int8_t command = data[0];
  switch (command)
  {
    // initialize sensors
    case 0x00: {
      u_int8_t sensorCount = data[1];
      if (sensors != nullptr) {
        delete sensors;
      }
      sensors = new MetalDetectorArray(sensorCount);
      for (u_int8_t i = 0; i < sensorCount; i++) {
        sensors->setSensor(i, data[2 + i]);
      }
      break;
    }
    // set raw data update rate
    case 0x01: {
      sendInterval = data[1]*10;
      break;
    }
    // enable/disable raw data updates
    case 0x02: {
      sendingData = (data[1] != 0);
      break;
    }
    // set sensor tresholds
    case 0x03: {
      u_int8_t tresholdCount = data[1];
      for (u_int8_t i = 0; i < min(tresholdCount, sensors->getCount()); i++) {
        uint16_t threshold = (data[2 + i * 2] << 8) | data[2 + i * 2 + 1];
        sensors->setThreshold(i, threshold);
      }
      break;
    }
    // enable/disable sensors
    case 0x04: {
      u_int8_t enableCount = data[1];
      for (u_int8_t i = 0; i < min(enableCount, sensors->getCount()); i++) {
        bool enabled = (data[2 + i] != 0);
        sensors->setEnabled(i, enabled);
      }
      break;
    }
    default:
      break;
  }
  return;
}

// constructs and sends sensor data packet
void sendSensorData() {
  if (sensors == nullptr) {
    return;
  }

  // check time of last packet sent
  static unsigned long lastSendTime_ms = 0;
  unsigned long currentTime_ms = millis();
  if (currentTime_ms - lastSendTime_ms < sendInterval) {
    return;
  }
  lastSendTime_ms = currentTime_ms;

  // construct packet
  u_int8_t size;
  u_int8_t* data;
  u_int8_t command = 0x00;
  int sensorCount = sensors->getCount();
  size = 2 + sensorCount * 2;

  int* values = new int[sensorCount];
  for (int i = 0; i < sensorCount; i++) {
    values[i] = sensors->readSensor(i);
  }

  data = new u_int8_t[size];
  data[0] = command;
  data[1] = sensorCount;
  for (int i = 0; i < sensorCount; i++) {
    data[2 + i * 2] = (values[i] >> 8) & 0xFF;
    data[2 + i * 2 + 1] = values[i] & 0xFF;
  }
  delete[] values;

  sendDataOverSerial(data, size);
  delete[] data;
}

// constructs and sends measurement packet
void sendMeasurements(double speed_m_per_s, double length_m, double width_m, double angle_deg) {
  u_int8_t* data;

  u_int8_t size = 1 + 4 * sizeof(double);
  u_int8_t command = 0x01;

  data = new u_int8_t[size];
  data[0] = command;
  memcpy(&data[1 + 0 * sizeof(double)], &speed_m_per_s, sizeof(double));
  memcpy(&data[1 + 1 * sizeof(double)], &length_m, sizeof(double));
  memcpy(&data[1 + 2 * sizeof(double)], &width_m, sizeof(double));
  memcpy(&data[1 + 3 * sizeof(double)], &angle_deg, sizeof(double));

  sendDataOverSerial(data, size);
  delete[] data;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  
  // fast blinking indicates that arduinos is not initialized
  // slow blinking means it is working as expected
  // added this to indicate crashes
  digitalWrite(LED_BUILTIN, ((millis()/(100*((sensors == nullptr) ? 1 : 10)))%2));

  // reading serial data and process them with a given function
  readSerialData(processSerialData);

  // send raw sensor data
  if (sendingData == true)
  {
    sendSensorData();
  }
  // measure
  Measurement measurements = measure(sensors);
  // send measurements if they are valid
  if (!fastIsNAN(measurements.speed_m_per_s) && !fastIsNAN(measurements.length_m) && !fastIsNAN(measurements.width_m) && !fastIsNAN(measurements.angle_deg)) {
    sendMeasurements(measurements.speed_m_per_s, measurements.length_m, measurements.width_m, measurements.angle_deg);
  }
}