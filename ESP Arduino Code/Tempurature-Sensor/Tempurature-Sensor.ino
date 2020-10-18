/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 21 
#define SleepSeconds 60
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 
void setup() 
{ 
 // start serial port and sensors
 Serial.flush();
 Serial.begin(115200);
 Serial.flush();
 sensors.begin();
 delay(1000);

 //Get Tempurature
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
 delay(10);
 t = (t1 + t2 + t3 + t4) / 4;
 Serial.println(t);

 //Go to Deep Sleep
 Serial.flush();
 Serial.end();
 esp_sleep_enable_timer_wakeup(SleepSeconds * 1000000);
 esp_deep_sleep_start(); 
} 
void loop() 
{ 
  //
} 
