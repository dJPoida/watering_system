/**
 * Store the cache data into SPIFFS
 */
bool storeCache() {
  Serial.println("Storing Cache...");

  File cacheFile = SPIFFS.open("/cache.csv", "w");
  if (!cacheFile) {
    Serial.println("Failed to write Cache. Could not open file.");
    return false;
  }

  // First value in the file is the last date the watering activity was run
  if (lastExecutedDate) {
    cacheFile.println(lastExecutedDate);
  }
  if (lastExecutedTime) {
    cacheFile.println(currentRTCTime());
  }
  
  cacheFile.close();

  return true;
}


/**
 * Load the cached data from SPIFFS
 */
bool restoreCache() {
  Serial.println("Restoring Cache...");
  
  File cacheFile = SPIFFS.open("/cache.csv", "r");
  if (!cacheFile) {
    Serial.println("No previous cache found.");
    return false;
  }

  // Read the first line as the last run date (YYYYMMDD)
  if (cacheFile.available()) {
    String lastExecutedDateString = cacheFile.readStringUntil('\n');
    lastExecutedDate = lastExecutedDateString.toInt();
  } 

  // Read the second line as the last run time (HHMMSS)
  if (cacheFile.available()) {
    String lastExecutedTimeString = cacheFile.readStringUntil('\n');
    lastExecutedTime = lastExecutedTimeString.toInt();
  } 
  
  cacheFile.close();

  if (lastExecutedDate && lastExecutedTime) {
    Serial.print("Watering last executed ");
    Serial.print(lastExecutedDate);
    Serial.print(" @ ");
    Serial.println(lastExecutedTime);    
  } else {
    Serial.println("No previous watering activity recorded.");    
  }

  return true;
}
