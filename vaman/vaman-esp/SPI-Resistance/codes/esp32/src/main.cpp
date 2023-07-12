#include <Arduino.h>
#include <SPI.h>
#include <ArduinoOTA.h>
#include <WebServer.h>
WebServer server(80);
#define SPI_CLK 1000000
SPIClass *hspi = NULL;
#ifndef STASSID
#define STASSID "hussain"  // Replace with your network credentials
#define STAPSK  "123456789"  
#endif
const char* ssid = STASSID;
const char* password = STAPSK;
void handleRoot() {
  // Read resistance value from Arduino slave over I2C
  int adcValue = analogRead(36); // Read analog value from pin A0 (GPIO 36)
  float voltage = adcValue * (5 / 4096.0); // Assuming ADC resolution of 12 bits (4096 levels)
  float knownResistance = 1000.0; // Change to the value of the known resistance (R2) in ohms
  float measuredResistance = (voltage * knownResistance) / (5 - voltage);
  Serial.println(measuredResistance);
  delay(1500);
  // Website Interface
  String html = "<html><body>";
  html += "<h1>Resistance Monitor</h1>";
  html += "<p>Measured Resistance-1: " + String(measuredResistance) + " Ohms</p>";
   //html += "<p>Measured Resistance-2: " + String(measuredResistance2) + " Ohms</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}
void setup() {
    Serial.begin(115200);
    hspi = new SPIClass(HSPI);
    hspi->begin();
    pinMode(hspi->pinSS(), OUTPUT);
    WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  SPI.begin();  // Initialize I2C communication as master

  server.on("/", handleRoot);

  server.begin();
  Serial.println("Web server started");
}
void spiCommand(SPIClass *spi, char data) {
    spi->beginTransaction(SPISettings(SPI_CLK, MSBFIRST, SPI_MODE0));
    digitalWrite(spi->pinSS(), LOW);
    spi->transfer(data);
    digitalWrite(spi->pinSS(), HIGH);
    spi->endTransaction();
}
void loop() {
  server.handleClient();
  delay(3000);
}




