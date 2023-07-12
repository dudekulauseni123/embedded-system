#include <Arduino.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
/*
#include "credentials.h"
consta ssid "hussain"  // Replace with your network credentials
#define password  "123456789" 
#define spiURL   "
*/
#define SPI_CLK 1000000
#define BUFFER_SIZE 32*8
const char *ssid = "hussain";
const char *password = "123456789";
const char *spiURL = "http://192.168.155.215:5000/spi";
SPIClass *hspi = NULL;
String rxbuf;
WiFiClient client;
HTTPClient spi;

void setup() {
    Serial.begin(115200);
    hspi = new SPIClass(HSPI);
    hspi->begin();
    pinMode(hspi->pinSS(), OUTPUT);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println();
    Serial.println(WiFi.localIP());
    spi.begin(client, spiURL);
}

void spiCommand(SPIClass *spi, char data) {
    spi->beginTransaction(SPISettings(SPI_CLK, MSBFIRST, SPI_MODE0));
    digitalWrite(spi->pinSS(), LOW);
    char rx = spi->transfer(data);
    rxbuf += rx;
    digitalWrite(spi->pinSS(), HIGH);
    spi->endTransaction();
}
void loop() {
    spi.addHeader("Content-Type", "application/json");
    StaticJsonDocument<512> doc;
    rxbuf = "";
    String msg = "Hello Arduino!\n";
    Serial.print("Sending to Arduino: ");
    Serial.print(msg);
    Serial.print("Received from Arduino: ");
    for (char ch : msg) spiCommand(hspi, ch);
    rxbuf += rxbuf[0];
    rxbuf = rxbuf.substring(1);
    Serial.print(rxbuf);
    doc["message"] = rxbuf;
    String requestBody;
    serializeJson(doc, requestBody);
    int httpResponseCode = spi.POST(requestBody);
    delay(1000);
}
