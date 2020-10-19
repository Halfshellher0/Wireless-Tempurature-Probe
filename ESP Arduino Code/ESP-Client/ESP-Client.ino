
/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 21 
#define SleepSeconds 60

const char* ssid     = "tplink";
const char* password = "11758341";
const char* deviceGUID = "dd561aea-8dc3-4e51-b7e7-12b1810e8a5b";

const uint16_t port = 8888;
const char* host = "192.168.0.100";

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  sensors.begin();
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(12000);
  ++value;

  //Get Tempurature
  Serial.println("getting tempurature reading");
  float t1, t2, t3, t4, t;
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  t1 = sensors.getTempCByIndex(0);
  delay(10); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  t2 = sensors.getTempCByIndex(0);
  delay(10);
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  t3 = sensors.getTempCByIndex(0);
  delay(10);
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  t4 = sensors.getTempCByIndex(0);

 
  t = (t1 + t2 + t3 + t4) / 4;
  String message = deviceGUID;
  message += ",";
  message += String(t,4);  

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient server;
  if (!server.connect(host, port)) {
    Serial.println("connection failed");
    delay(1000);
    return;
  }
  
  // This will send the request to the server
  server.print(message); 
  unsigned long timeout = millis();
  while (server.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      server.stop();
      return;
    }
  }
  Serial.println("Sent Hello");
  
  // Read all the lines of the reply from server and print them to Serial
  while(server.available()){
    String line = server.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
