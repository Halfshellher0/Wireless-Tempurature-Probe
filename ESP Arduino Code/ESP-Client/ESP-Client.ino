
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
  delay(100);
  ++value;

  //Get Tempurature
  Serial.println("getting tempurature reading");
  float t1, t2, t;
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  t1 = sensors.getTempCByIndex(0);
 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  t2 = sensors.getTempCByIndex(0);
 
  t = (t1 + t2) / 2;
  Serial.print("t = ");
  Serial.println(t,4);

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(1000);
    return;
  }
  
  // This will send the request to the server
  client.print(t,4);  
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  Serial.print("Sent Hello");
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
