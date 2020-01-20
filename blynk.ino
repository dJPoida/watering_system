#include "config.h"

/**
 * Setup and connect to the Blynk server
 */
bool connectToBlynk() {
  Serial.println("Connecting to Blynk...");
  Blynk.begin(blynkAuthToken, ssid, pass);

  // Activating the RTC widget asap is required to get the current time ASAP
  rtc.begin();

  // Wait for Blynk to be connected with a max timeout of X milliseconds
  long startMillis = millis();
  while(!Blynk.connected()) { 
    // If connecting to the Blynk service takes longer than the connection timeout,
    // exit with a fail result.
    if ((millis() - startMillis) > BLYNK_CONNECTION_TIMEOUT) {
      Serial.println("Blynk connection failed");
      return false;
    }
  }

  // Wait for the rtc to sync to the server
  startMillis = millis();
  while(year() == 1970) {
    Blynk.run();
    // If waiting for the rtc to sync with the server takes nmore than the connection timeout then
    // exit with a fail result.
    if ((millis() - startMillis) > BLYNK_CONNECTION_TIMEOUT) {
      Serial.println("Blynk RTC sync failed");
      return false;
    }
  }

  // Return with a success result
  Serial.println("Blynk Connected");
  serialPrintCurrentDateAndTime();
  
  return true;
}


/**
 * This is fired when Blynk Connects to the server
 * We use this event to re-sync all of the Blynk app
 * config to the device.
 */
BLYNK_CONNECTED() {
  // Request Blynk server to re-send latest values for all pins
  Blynk.syncAll();
}


/**
 * This is fired when the Blynk app sends the
 * time that the daily watering activitiy should occurr
 */
BLYNK_WRITE(PIN_BLYNK_RUN_TIME) {
  TimeInputParam t(param);
  if (t.hasStartTime()) {
    dailyWateringTime = formatTimeAsLong(t.getStartHour(), t.getStartMinute(), t.getStartSecond());
    dailyWateringTimeInSeconds = param[0].asLong();
  }
  
  Serial.print("Daily watering time: ");
  Serial.println(dailyWateringTime);
}


/**
 * This is fired when the Blynk app sends the
 * duration that the pump should run for as set by the slider in the app
 */
BLYNK_WRITE(PIN_BLYNK_PUMP_DURATION) {
  pumpDuration = (param[0].asLong() * 1000);
  
  Serial.print("Pump Duration: ");
  Serial.println(pumpDuration);
}

/**
 * This is fired when the Blynk app sends whether the App
 * is configured to receive push notifications or not
 */
BLYNK_WRITE(PIN_BLYNK_ALERTS_ENABLED) {
  sendAlertsEnabled = param[0].asInt();
  
  Serial.print("Send Alerts: ");
  Serial.println(sendAlertsEnabled ? "Enabled" : "Disabled");
}


/**
 * This is fired when the Blynk app sends whether the App
 * is configured to force the watering routine to run 
 * regardless of whether the routine has already been run today.
 */
BLYNK_WRITE(PIN_BLYNK_FORCE_WATER) {
  forceWaterRoutine = param[0].asInt();
  
  Serial.print("Force Watering Routine: ");
  Serial.println(forceWaterRoutine ? "Enabled" : "Disabled");
}



/**
 * Simple debug function to output the result of an RTC sync
 */
void serialPrintCurrentDateAndTime() {
  char dateTimeBuffer[19];
  sprintf(dateTimeBuffer, "%04d-%02d-%02d %02d:%02d:%02d",  year(), month(), day(), hour(), minute(), second());

  Serial.print("Current date/time: ");
  Serial.println(dateTimeBuffer);
}


/**
 * Send the alerts about low water or low battery
 */
void sendAlerts() {
  // Activate / deactivate the low water LED
  if (waterOk) {
    blynkLED_lowWater.off();
  } else {
    blynkLED_lowWater.on();
  }

  // Activate / deactivate the low battery LED
  if (batteryOk) {
    blynkLED_lowBattery.off();
  } else {
    blynkLED_lowBattery.on();
  }

  // Deactivate the force watering routine buttton
  if (forceWaterRoutine) {
    Blynk.virtualWrite(PIN_BLYNK_FORCE_WATER, 0);
  }
  
  // Send the alert via the notification widget  
  if (sendAlertsEnabled && (!waterOk || !batteryOk)) {
    String alert = "Watering System:";
    
    if (!batteryOk) {
      alert = alert + " *Battery Low*";
    }

    if (!waterOk) {
      alert = alert + "*Water Low*";
    }
    
    Blynk.notify(alert);
  }
}


/**
 * Send the report to the blynk terminal about the execution
 */
void sendReport() {
  Serial.println("Sending report to Blynk Terminal");
  
  terminal.println(F("====================="));
  terminal.print(F("["));
  terminal.print(currentTimeStamp());
  terminal.println(F("]"));
  terminal.println(F("---------------------"));

  if (wateringExecuted) {
    if (forceWaterRoutine) {
      terminal.println(F("Forced watering routine executed."));
    } else {
      terminal.println(F("Scheduled Watering routine executed."));
    }
    terminal.print(F("Watered for "));
    terminal.print(((int)(pumpDuration / 1000)));
    terminal.println(F("s."));
  } else {
    if (wateringAlreadyRunToday()) {
      terminal.print(F("Next Water: Tomorrow at "));
      terminal.println(secondsToHHMMSS(dailyWateringTimeInSeconds));
    } else {
      terminal.print(F("Next Water: Today at "));
      terminal.println(secondsToHHMMSS(dailyWateringTimeInSeconds));
    }
  }

  if (!batteryOk) {
    terminal.println(F("WARNING: BATTERY LOW"));
  }

  if (!waterOk) {
    terminal.println(F("WARNING: WATER TANK LOW"));
  }

  terminal.print(F("Next Wake: "));
  terminal.println(nextWakeTime());
  terminal.println(F("---------------------"));
  terminal.println(F(""));

  terminal.flush();
}
