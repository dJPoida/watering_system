#include "config.h"

/**
 * Setup the pump
 */
void setupPump() {
  pinMode(PIN_PUMP, OUTPUT);
  digitalWrite(PIN_PUMP, LOW);
}


/**
 * Actiates the water pump
 */
void pumpOn() {
  Serial.println("Pump: On");
  digitalWrite(PIN_PUMP, HIGH);
}


/**
 * Deactivates the water pump
 */
void pumpOff() {
  Serial.println("Pump: Off");
  digitalWrite(PIN_PUMP, LOW);
}


/**
 * Execute the watering routine
 */
void executeWateringRoutine() {
  lastExecutedDate = currentRTCDate();
  lastExecutedTime = currentRTCTime();
  wateringExecuted = true;
  
  Serial.println("########");
  Serial.println("WATERING... ");
  Serial.println("########");

  ledOn();
  pumpOn();
  long timeStarted = millis();
  while ((millis() - timeStarted) < pumpDuration) {
    delay(50);
  }
  pumpOff();
  ledOff();
}
