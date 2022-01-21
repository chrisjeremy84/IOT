
#include "thingProperties.h"
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 15
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHT11);
int led = 8;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(500); 

  // Defined in thingProperties.h
  initProperties();
  
  //LED
  pinMode(led, OUTPUT);
  
  dht.begin();
    
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  delay(2000);
  boardTEMP = dht.readTemperature();
  humidity = dht.readHumidity();
}

/*
  Since LED is READ_WRITE variable, onLEDChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLEDChange()  {
  // Add your code here to act upon LED change
  Serial.print(LED);
  if(LED){
    digitalWrite(LED_BUILTIN, HIGH);
  }else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  
}
