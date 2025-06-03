#include <Wire.h>
#include <Adafruit_INA219.h>
#include "BluetoothSerial.h"

Adafruit_INA219 ina219;
BluetoothSerial SerialBT;

const int V1_pin = 34;
const int Vload_pin = 35;

void setup() {
  SerialBT.begin("ESP32_Meter");

  Wire.begin();
  ina219.begin();

  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);
}

void loop() {
  float current_A = ina219.getCurrent_mA() / 1000.0;
  float V1 = analogRead(V1_pin) * (3.3 / 4095.0) * 2.0;     // 분압 보정
  float Vload = analogRead(Vload_pin) * (3.3 / 4095.0); 

  // 블루투스 출력
  SerialBT.print(current_A, 5); SerialBT.print(" ");
  SerialBT.print(V1, 3); SerialBT.print(" ");
  SerialBT.println(Vload, 3);

  delay(1000);
}
