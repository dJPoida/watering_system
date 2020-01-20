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

// Blynk Low Water LED
WidgetLED blynkLED_lowWater(PIN_BLYNK_LOW_WATER_LED);

// Blynk Low Battery LED
WidgetLED blynkLED_lowBattery(PIN_BLYNK_LOW_BATTERY_LED);

// Boolean for water level OK
bool waterOk = true;

// Boolean for battery level OK
bool batteryOk = true;

// Boolean to determine if we're connected to Blynk
bool connectedToBlynk = false;

// Boolean to control whether the app wants push notifications or not
bool sendAlertsEnabled = false;

// Boolean to override whether the watering routine should be run or not
bool forceWaterRoutine = false;

// Boolean to flag whether or not the watering routine was executed
bool wateringExecuted = false;

// The duration the pump should run for (in seconds)
int pumpDuration = 5000;

// The time of day the watering activity is supposed to take place (HHMMSS)
long dailyWateringTime = 0;

// The time of day the watering activity is supposed to take place in seconds()
long dailyWateringTimeInSeconds = 0;

// the number of seconds until the next watering routine should be executed
long timeUntilNextWaterInSeconds = 0;

// The date the watering activity was last run (YYYYMMDD)
long lastExecutedDate = 0;

// The time of day the watering activity was last run (HHMMSS)
long lastExecutedTime = 0;

// The time the device should sleep for (in microseconds)
uint64_t sleepDuration = SLEEP_DEFAULT;

// The time the device should sleep for (in seconds)
long sleepDurationInSeconds = SLEEP_DEFAULT / 1000000;


/**
 * The main routine runs in setup.
 */
void setup() {
  Serial.begin(9600);
  Serial.println("Awake.");

  // Setup the peripherals
  SPIFFS.begin();
  setupLED();
  setupPump();
  setupWaterSensor();

  // Connect ot the Blynk service()
  connectedToBlynk = connectToBlynk();

  // restore the cache
  restoreCache();

  // check the battery
  checkBattery();

  // check the water
  checkWater();

  // send any alerts
  sendAlerts();

  // calculate the time until the next watering event
  calculateTimeUntilNextWater();

  // Run the watering routine (if required)
  if ((!wateringAlreadyRunToday() && (timeUntilNextWaterInSeconds < 0)) || forceWaterRoutine) {
    executeWateringRoutine();
  }
  
  // store the cache
  storeCache();

  // Calculate how long the device should sleep for
  calculateNextSleepDuration();

  // Send the report to Blynk
  sendReport();

  // sleep
  sleep();
}

void loop() {
  // de nada. Everything happens in setup.
}
