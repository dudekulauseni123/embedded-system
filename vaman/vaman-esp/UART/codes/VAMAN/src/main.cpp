#include <Wire.h>
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = ".....";  // Replace with your network credentials
const char* password = ".....";   

WebServer server(80);

float measuredResistance1 = 0.0;  // Variable to store the received resistance value
float measuredResistance2 = 0.0; 
void handleRoot() {
  // Read resistance value from Arduino slave over I2C
  Wire.requestFrom(8, sizeof(float));  // Request data from Arduino slave with address 8
  if (Wire.available() >= sizeof(float)) {
    Wire.readBytes((byte*)&measuredResistance1, sizeof(measuredResistance1));  // Read the float value
  }
  delay(1000);
  Wire.requestFrom(8, sizeof(float));  // Request data from Arduino slave with address 8
  if (Wire.available() >= sizeof(float)) {
    Wire.readBytes((byte*)&measuredResistance2, sizeof(measuredResistance2));  // Read the float value
  }
  
  

  // Website Interface
  String html = "<html><body>";
  html += "<h1>Resistance Monitor</h1>";
  html += "<p>Measured Resistance: " + String(measuredResistance1) + "," + String(measuredResistance2) + " Ohms</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

#define RXp2 21
#define TXp2 22

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  Wire.begin();  // Initialize I2C communication as master

  server.on("/", handleRoot);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
  delay(3000);
}

