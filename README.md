# ZPA4756-0311A-R Arduino Library

This Arduino library provides an easy-to-use interface for controlling the Murata ZPA4756-0311A-R barometric pressure sensor. It supports both SPI and I2C communication protocols and allows you to configure and read pressure and temperature data from the sensor.

## Features

- Compatible with I2C interfaces.
- Read barometric pressure (Pa) with high precision.
- Read temperature (°C) with excellent accuracy.
- Configure measurement modes: Continuous or One-Shot.
- Low power consumption and standby mode support.

## Installation

1. Clone or download this repository.
2. Open Arduino IDE.
3. Go to **Sketch > Include Library > Add .ZIP Library**.
4. Select the downloaded library folder.

Alternatively, you can install it via the Arduino Library Manager (once published).

## Usage

### Example Sketch

```cpp
#include <Wire.h>
#include "ZPA4756_0311A_R.h"

ZPA4756_0311A_R sensor;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Wire.begin();
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
```