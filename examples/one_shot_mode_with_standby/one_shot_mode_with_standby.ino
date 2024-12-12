#include <Wire.h>
#include "ZPA4756_0311A_R.h"

ZPA4756_0311A_R sensor;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Wire.begin();

  sensor.setStandbyTime(STBY_1000_MS);
  sensor.setOversamplingRate(OSR_4096);
  sensor.begin();
}

void loop() {
  if (sensor.readMeasurements(false)) {  // blockingにfalseを指定すると変換が完了していなければ戻り値falseを返す.
    float pressure = sensor.getPressure();
    float temperature = sensor.getTemperature();
    Serial.print(pressure, 5);
    Serial.print(" ");
    Serial.print(temperature, 5);
    Serial.println();
  } else {
    // 何か処理をする
    delay(50);
  }
}
