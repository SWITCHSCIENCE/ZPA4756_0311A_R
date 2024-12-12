#include <Wire.h>
#include "ZPA4756_0311A_R.h"

ZPA4756_0311A_R sensor;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Wire.begin();

  // sensor.setOversamplingRate(OSR_4096);
  sensor.begin();
}

void loop() {
  if (sensor.readMeasurements()) {
    float pressure = sensor.getPressure();
    float temperature = sensor.getTemperature();
    Serial.print(pressure, 5);
    Serial.print(" ");
    Serial.print(temperature, 5);
    Serial.println();
  }
}
