#include "config.h"

/**
 * LED Setup
 */
void setupLED() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
}


/**
 * Turn the LED on
 */
void ledOn() {
  Serial.println("LED: On");
  digitalWrite(PIN_LED, HIGH);
}


/**
 * Turn the LED off
 */
void ledOff() {
  Serial.println("LED: Off");
  digitalWrite(PIN_LED, LOW);  
}
