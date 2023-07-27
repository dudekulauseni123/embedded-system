#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include"libr.h"

AsyncWebServer server(80);

const char* ssid = "Madhu";
const char* password = "1234567890";

const char* input_parameter00 = "input00";
const char* input_parameter01 = "input01";
const char* input_parameter02 = "input02";
const char* input_parameter10 = "input10";
const char* input_parameter11 = "input11";
const char* input_parameter12 = "input12";
const char* input_parameter20 = "input20";
const char* input_parameter21 = "input21";
const char* input_parameter22 = "input22";
const char* matrix1[3]={input_parameter00,input_parameter01,input_parameter02};
const char* matrix2[3]={input_parameter10,input_parameter11,input_parameter12};
const char* matrix3[3]={input_parameter20,input_parameter21,input_parameter22};

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>COLLINEARITY</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {font-family: Times New Roman; display: inline-block; text-align: center;}
    h2 {font-size: 2.0rem; color: blue;}
  </style> 
  </head><body>
  <h2>TO FIND IF POINTS ARE COLLINEAR OR NOT</h2> 
  <p>Enter the values of points A,B,C
  <form action="/get">
    Enter the values of Point A: <input type="number" name="input00"><br><input type="number" name="input01"><br><input type="number" name="input02"><br>
    Enter the values of Point B: <input type="number" name="input10"><br><input type="number" name="input11"><br><input type="number" name="input12"><br>
    Enter the values of Point C: <input type="number" name="input20"><br><input type="number" name="input21"><br><input type="number" name="input22"><br>
    <input type="submit" value="Submit">
    

  </form><br>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connecting...");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    double **A,**B,**C,**d,**e,**one,**f,**k;
    double m=3,n=1,s,two;
    A=load_ser(request,matrix1);
    B=load_ser(request,matrix2);
    C=load_ser(request,matrix3);
    d=linalg_sub(B,A,m,n);
    e=linalg_sub(C,B,m,n);
    k=block(A,B,C,m,n);
    int o;
    o=rank(k,m);
    if(o<3)
    {
    	f=transpose(e,m,n);
	one=mat_mul(f,d,n,m,n);
	two=linalg_norm(e,m);
	s=one[0][0]/two;
	request->send(200, "text/html", "The points are collinear<b> B divides AC in the ratio: "+ String(s,2) + ")<br><a href=\"/\">Return to Home Page</a>");}

    else{
	request->send(200, "text/html", "The points are not collinear <br><a href=\"/\">Return to Home Page</a>");

    }


  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
