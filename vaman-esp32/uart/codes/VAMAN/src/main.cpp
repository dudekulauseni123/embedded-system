#include <WiFi.h>
#include <WebServer.h>

const char* ssid = ".....";  // Replace with your network credentials
const char* password = ".....";   

WebServer server(80);

void handleRoot() {

    String RxM = Serial2.readString();

//Website Interface
  String html = "<html><body>";
  html += "<h1>Resistance Monitor</h1>";
  html += "<p>Measured Resistance: " + RxM + " Ohms</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

#define RXp2 16
#define TXp2 17
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  
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
    delay(3000);
}
