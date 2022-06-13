#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 // Data wire is plugged into pin 2 on the arduino

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

unsigned long lastsend;
float SMpin = A0;

void setup() 
{
  Serial.begin(1152000);

  sensors.begin();
  delay(10);
  lastsend = 0;
}

void loop() 
{
  if ( millis() - lastsend > 1000 ) 
  { // update and send only after 1 seconds 
    getSoilTemperatureAndMoistureData();
    lastSend = millis();
  }
} 
void getSoilTemperatureAndMoistureData()
{
  Serial.println("Collecting Moisture Precentage");
   
  float moisture_percentage;

  moisture_percentage = (100.00 - ((analogRead(SMpin)/1023.00) * 100.00));

  //if any reads fail and exit early (to try again).
  if (isnan(moisture_percentage)) 
  {
    Serial.println("Failedto read Soil Moisture value!");
    return;
  }
  Serial.println("Soil Moisture:");
  Serial.println(moisture_percentage);
  Serial.println(" %\t");
}
  
