/**
 * Calculate the time (in seconds) until the next watering routine)
 * If the watering has already happened today, timeUntilNextWaterInSeconds will be set to 0
 */
void calculateTimeUntilNextWater() {
  if (wateringAlreadyRunToday()) {
    timeUntilNextWaterInSeconds = 0;
    return;
  } 

  // Take the time the daily watering event is supposed to run and subtract the current time in seconds
  timeUntilNextWaterInSeconds = dailyWateringTimeInSeconds - currentRTCTimeInSeconds();
}


/**
 * Calculate the time the device should sleep for.
 * If the watering routine is expected to fire within the default sleep 
 * duration (SLEEP_DEFAULT) then use the time between now and the next
 * run as the sleep duration. Otherwise use the default.
 * 
 * Note: This has a limitation that start times between midnight and SLEEP_DEFAULT
 * won't work. Can't be bothered solving for this as I'm not planning on watering
 * in the pitch black of night.
 */
void calculateNextSleepDuration() {
  // If the watering routine has not run today, check to see if the time until 
  // the next run is less than the default sleep duration. Remembering that the
  // sleep durations are in microseconds (us) and the timers are in seconds (^6)
  if (!wateringAlreadyRunToday()){
    if (timeUntilNextWaterInSeconds < (sleepDuration / 1000000)) {
      sleepDuration = timeUntilNextWaterInSeconds * 1000000;
    }
  } else {
    sleepDuration = SLEEP_DEFAULT;
  }
  sleepDurationInSeconds = sleepDuration / 1000000;
  
  Serial.print("Sleep duration: ");
  Serial.print(sleepDurationInSeconds);
  Serial.println("s");
}


/**
 * Simply evaluates whether the watering routine has already run today.
 */
bool wateringAlreadyRunToday() {
  return (lastExecutedDate == currentRTCDate());
}


/**
 * Put the device to sleep
 */
void sleep() {
  // Put a delay here just to make sure all Blynk values are synced with the server
  long startMillis = millis();
  while ((millis() - startMillis) < 1000) {
    Blynk.run();
    delay(10);
  }
  Serial.println("Putting device to sleep.");
  ESP.deepSleep(sleepDuration);
}
