#include "Arduino.h"

float measuredResistance = 0.0;

void setup() {
  Serial.begin(9600);
}
void loop() {
  int adcValue = analogRead(A0);
  float voltage = adcValue * (5.0 / 1024.0);
  float knownResistance = 1000.0; // Change to the value of the known resistance (R2) in ohms
  measuredResistance = (voltage * knownResistance) / (5.0 - voltage);
  Serial.println(measuredResistance);
  delay(1500);
}

