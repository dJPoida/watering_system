/**
 * dJPoida's Watering System
 * Peter Eldred 2020-01
 * License: MIT
 * 
 * Board: Wemos D2
 * Peripherals:
 *  - Capacitive Soil Moisture Sensor for detecting water tank water out level
 *  - Brushless 12v DC Submersable Pump AD20P-1230C
 *  - LED for physical running indication
 * 
 * Program only runs once then sleeps until next scheduled run time
 * 
 * Procedure:
 *  - Wake
 *  - Water
 *  - Check tank level
 *  - Determine next run time (sunrise / sunset)
 *  - Send report (or alert if required)
 *  - Sleep 
 */
#include "config.h"

// At what level should the moisture sensor consider the water to have run out (larger number = less water)
#define waterOutLevel 700

// For how many milliseconds should the pump run (60000 = 60 seconds)
#define pumpDuration 5000

// The water level sensor is only activated when required by setting this pin HIGH
#define PIN_WATER_LEVEL_POWER D4

// The water level is read on this pin
#define PIN_WATER_LEVEL A0

// This pin activates the water pump
#define PIN_PUMP D8

// This pin controlls the attached LED
#define PIN_LED D7

// This pin simply registerd whether the battery is low or not.
#define PIN_BATTERY D2



bool waterOk = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Wasup!");

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  pinMode(PIN_PUMP, OUTPUT);
  digitalWrite(PIN_PUMP, LOW);
  
  pinMode(PIN_WATER_LEVEL_POWER, OUTPUT);
  pinMode(A0, INPUT);

  digitalWrite(PIN_LED, LOW);
}

void loop() {
  
  //checkWater();
  //pump();
  checkBattery();

  delay(1000);
}

void checkBattery() {
  bool batteryOk = digitalRead(PIN_BATTERY);
  Serial.print("Battery ");
  if (batteryOk) {
    Serial.println("OK");
  } else {
    Serial.println("Low");
  }
}

void checkWater() {
  digitalWrite(PIN_WATER_LEVEL_POWER, HIGH);
  delay(100);
  int reading = analogRead(A0);
  // Serial.println(reading);
  bool oldWaterOk = waterOk;
  bool newWaterOk = reading < waterOutLevel;
  if (newWaterOk != oldWaterOk) {
    if (newWaterOk) {
      Serial.println("Water: Ok");
    } else {
      Serial.println("Water: NOT OK!!!!");
    }
    waterOk = newWaterOk;
  }
  digitalWrite(PIN_WATER_LEVEL_POWER, LOW);
  delay(1000);
}

void pump() {
  Serial.println("Pump On");
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_PUMP, HIGH);
  delay(3000);
  Serial.println("Pump off");
  digitalWrite(PIN_PUMP, LOW);
  digitalWrite(PIN_LED, LOW);
}
