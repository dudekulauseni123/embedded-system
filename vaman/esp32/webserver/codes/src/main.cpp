#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ARUN_KUMAR";
const char* password = "arunkumar";

WebServer server(80);
float measuredResistance = 0.0;

void handleRoot() {

  int adcValue = analogRead(34);
  float voltage = adcValue * (5.0 / 4095.0);
  float knownResistance = 1000.0; // Change to the value of the known resistance (R2) in ohms
  measuredResistance = (voltage * knownResistance) / (5.0 - voltage);
  
  //Website Interface
  String html = "<html><body>";
  html += "<h1>Resistance Monitor</h1>";
  html += "<p>Measured Resistance: " + String(measuredResistance, 2) + " Ohms</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", handleRoot);

  server.begin();
  Serial.println("Web server started");
}

void loop() {

  server.handleClient();
}



