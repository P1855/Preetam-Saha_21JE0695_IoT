#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 // Data wire is plugged into pin 2 on the Arduino

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
unsigned long lastSend ;
float SMpin = A0;
int actPin = 13; //Actuator(motor) connected to pin 13
float smThres = 75.0; //Threshold for triggering actuator - 75%
int spMotor = 180; //Current Soil Moisture value in percentage value as 0

void setup ()
{
  Serial.begin(115200);
  pinMode(13,OUTPUT); //Set pin 13 as OUTPUT pin
  sensors.begin();
  delay(10);lastSend = 0;
}

void loop()
{
  if (millis() - lastSend > 1000 ) { // Update and send only after 1 second
    moisPercent = getSoilTemperatureAndMoistureData();
    if (moisPercent <= smThres){
      analogWrite(actPin, spMotor);// turns on the motor
    }
    else {
      analogWrite(actPin, spMotor); // turns on the motor  
    }
    lastSend = millis();
  }
}

float getSoilTemperatureAndMoistureData()
{
  Serial.println("Collecting Moisture Percentage");

  float moisture_percentage;

  moisture_percentage = (100.00 - ((analogRead(SMpin)/1023.00) * 100.00 ));

  // if any reads fail and exit early (to try again).
  if (isnan(moisture_percentage)) {
    Serial.println("Failed to read Soil Moisture value!");
    return 999;
    }
    Serial.print("Soil Moisture: ");
    Serial.print(moisture_percentage);
    Serial.print("%\t");
    return moisture_percentage;
}
