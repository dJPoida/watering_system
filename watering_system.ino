/**
 * dJPoida's Watering System
 * Peter Eldred 2020-01
 * License: MIT
 * 
 * Board: Wemos D1 R2
 * Peripherals:
 *  - Capacitive Soil Moisture Sensor for detecting water tank water out level
 *  - Brushless 12v DC Submersable Pump AD20P-1230C
 *  - LED for physical running indication
 *  - DC Relay
 *  - 9v Power Supply (6x AA Cells)
 *  - Step-up Buck Converter tuned to 12v
 */
#include "config.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <FS.h>
#include <WidgetRTC.h>


// Globals

// Blynk Terminal Widget
WidgetTerminal terminal(PIN_BLYNK_TERMINAL);

// Blynk RTC Widget
WidgetRTC rtc;

// Boolean for water level OK
bool waterOk = false;

// Boolean for battery level OK
bool batteryOk = false;

/**
 * The main routine runs in setup.
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Wasup!");

  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);

  pinMode(PIN_PUMP, OUTPUT);
  digitalWrite(PIN_PUMP, LOW);
  
  pinMode(PIN_WATER_LEVEL_POWER, OUTPUT);
  pinMode(PIN_WATER_LEVEL, INPUT);

  digitalWrite(PIN_LED, LOW);

  // checkWater();
  // pump();
  // checkBattery();

  // delay(1000);
}

void loop() {
  // de nada 
}
