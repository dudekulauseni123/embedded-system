#include <Arduino.h>
#include <Wire.h>
float value1 = 0.0;

void sendData() {
int adcValue = analogRead(A0);
  float voltage = adcValue * (5.0 / 1023.0);
  float knownResistance = 1000.0; // Change to the value of the known resistance (R2) in ohms
  value1 = (voltage * knownResistance)/ (5.0 - voltage); ;
  Wire.write((byte*)&value1, sizeof(value1)); // Send data to the master
 

  Serial.println("Data sent");  // Print a message to the serial monitor
}

void setup() {
  Wire.begin(8);  // Initialize I2C communication with address 8
  Wire.onRequest(sendData);  // Register the sendData function to handle requests

  Serial.begin(9600);  // Initialize the serial monitor
  while (!Serial);  // Wait for the serial connection to be established
}

void loop() {
 
}
