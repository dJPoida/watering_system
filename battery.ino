/**
 * Check the level of the battery.
 * Since the ESP8266 only has a single analogue pin, this is done digitally
 * using a voltage divider.
 */
void checkBattery() {
  Serial.print("Checking Battery... ");
  batteryOk = digitalRead(PIN_BATTERY);
  if (batteryOk) {
    Serial.println("OK");
  } else {
    Serial.println("Low");
  }
}
