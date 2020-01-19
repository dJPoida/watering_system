/**
 * Check the water level.
 * The water level is connected to the only Analogue sensor
 * so if the water level is below the waterOut level then the
 * water = not ok!
 */
void checkWater() {
  Serial.print("Checking Water Level... ");

  // Activate the water sensor
  digitalWrite(PIN_WATER_LEVEL_POWER, HIGH);
  
  delay(100);

  // Take a reading
  int reading = analogRead(PIN_WATER_LEVEL);

  // Deactivate the water sensor
  digitalWrite(PIN_WATER_LEVEL_POWER, LOW);

  // Is the reading less than the water "out" level?
  waterOk = reading < waterOutLevel;
  if (waterOk) {
    Serial.println("Ok");
  } else {
    Serial.println("Low");
  }
}
