#if defined(ESP8266)
  #include<ESP8266WiFi.h>
//  #pragma message "ESP8266 stuff happening!"
#elif defined(ESP32)
  #include<WiFi.h>
//  #pragma message "ESP32 stuff happening!"
#else
//  #error "This ain't a ESP8266 or ESP32"
#endif

//sudo chmod a+rw /dev/ttyUSB0 run this if got error
WiFiClient client;
WiFiServer server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 4, 4);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);

#define led 12

void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);
  WiFi.softAP("hussain", "hussain12345");
  #WiFi.softAP("ssid", "password");
  Serial.println();
  Serial.println("NodeMCU Started!");
  Serial.println(WiFi.softAPIP());
  if (!WiFi.config(local_IP, gateway, subnet)) {
  Serial.println("STA Failed to configure");
}
  Serial.println(WiFi.localIP());
  server.begin();
  pinMode(led, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.    
  if (client == 1)
  {  
      String req = client.readStringUntil('\r');
      client.flush();
      if(req.indexOf("/forward") != -1)
      {Serial.println("Forward");
      ////digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,HIGH);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/backward") != -1)
      {Serial.println("Backward");
      //digitalWrite(16,LOW);
      //digitalWrite(17,HIGH);
      //digitalWrite(18,LOW);
      //digitalWrite(19,HIGH);
      }
      else if(req.indexOf("/left") != -1)
      {Serial.println("Left");
      //digitalWrite(16,LOW);
      //digitalWrite(17,LOW);
      //digitalWrite(18,HIGH);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/right") != -1)
      {Serial.println("Right");
      //digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,LOW);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/stop") != -1)
      {Serial.println("Stop");
      //digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,LOW);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/start") != -1)
      {Serial.println("Start");
      //digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,LOW);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/cross") != -1)
      {Serial.println("Cross");
      //digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,LOW);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/circle") != -1)
      {Serial.println("Circle");
      //digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,LOW);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/square") != -1)
      {Serial.println("Square");
      //digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,LOW);
      //digitalWrite(19,LOW);
      }
      else if(req.indexOf("/triangle") != -1)
      {Serial.println("Triangle");
      //digitalWrite(16,HIGH);
      //digitalWrite(17,LOW);
      //digitalWrite(18,LOW);
      //digitalWrite(19,LOW);
      }
  }
}

//    String request =  client.readStringUntil('\n');
//    Serial.println(request);
//    request.trim();
//    if(request == "GET /ledon HTTP/1.1")
//    {
//      digitalWrite(led, HIGH);
//    }
//    if(request == "GET /ledoff HTTP/1.1")
//    {
//      digitalWrite(led, LOW);
//    }
