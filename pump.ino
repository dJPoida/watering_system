#include "config.h"

/**
 * Actiates the water pump
 */
void activatePump() {
  Serial.println("Pump On");
  digitalWrite(PIN_LED, HIGH);
  digitalWrite(PIN_PUMP, HIGH);
}


/**
 * Deactivates the water pump
 */
void deactivatePump() {
  Serial.println("Pump Off");
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_PUMP, LOW);
}
