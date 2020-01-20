#include "config.h"

/**
 * Setup the water sensor
 */
void setupWaterSensor() {
  pinMode(PIN_WATER_LEVEL_POWER, OUTPUT);
  digitalWrite(PIN_WATER_LEVEL_POWER, LOW);
  pinMode(PIN_WATER_LEVEL, INPUT);
}


/**
 * Check the water level.
 * The water level is connected to the only analog sensor
 * so if the water level is below the waterOut level then the
 * water = not ok!
 */
void checkWater() {
  Serial.print("Water Level: ");

  // Activate the water sensor
  digitalWrite(PIN_WATER_LEVEL_POWER, HIGH);
  
  delay(100);

  // Take a reading
  int reading = analogRead(PIN_WATER_LEVEL);

  // Deactivate the water sensor
  digitalWrite(PIN_WATER_LEVEL_POWER, LOW);

  // Is the reading less than the water "out" level?
  waterOk = reading < WATER_OUT_LEVEL;
  if (waterOk) {
    Serial.println("Ok");
  } else {
    Serial.println("Low");
  }
}
