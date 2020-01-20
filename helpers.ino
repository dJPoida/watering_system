/**
 * Get the current RTC date as a long formatted YYYYMMDD
 */
long currentRTCDate() {
  return formatDateAsLong(year(), month(), day());
}


/**
 * Get the current RTC time as a long formatted HHMMSS
 */
long currentRTCTime() {
  return formatTimeAsLong(hour(), minute(), second());
}


/**
 * Get the current RTC time in seconds
 */
long currentRTCTimeInSeconds() {
  return (hour() * 60 * 60) + (minute() * 60) + second();
}


/**
 * Format Hour, Minute and Second time values as a single long
 * encoded as HHMMSS
 */
long formatTimeAsLong(int tHour, int tMinute, int tSecond) {
  char timeBuffer[6];
  sprintf(timeBuffer, "%02d%02d%02d", tHour, tMinute, tSecond);
  return String(timeBuffer).toInt();
}


/**
 * Format Year, Month and Day values as a single long
 * encoded as YYYYMMDD
 */
long formatDateAsLong(int dYear, int dMonth, int dDay) {
  char dateBuffer[8];
  sprintf(dateBuffer, "%04d%02d%02d", dYear, dMonth, dDay);
  return String(dateBuffer).toInt();
}


/**
 * Format the current timestamp in "YYYY-MM-DD HH:MM:SS"
 */
String currentTimeStamp() {
  char dateTimeBuffer[19];
  sprintf(dateTimeBuffer, "%04d-%02d-%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());
  return String(dateTimeBuffer);
}


/**
 * Takes the sleepDurationInSeconds and appends it to the current time
 * then returns the result in HH:MM:SS
 */
String nextWakeTime() {
  long nextWakeTime = currentRTCTimeInSeconds() + sleepDurationInSeconds;
  return secondsToHHMMSS(nextWakeTime);
}


/**
 * Format a time in seconds to an Hours, Minutes and Seconds string (HH:MM:SS)
 */
String secondsToHHMMSS (long timeInSeconds) {
  long hours = timeInSeconds / 3600;
  long remainder = timeInSeconds % 3600;
  long minutes = remainder / 60;
  long seconds = remainder % 60;
  
//  if (hours > 24) {
//    hours = 0;
//  }

  char timeBuffer[8];
  sprintf(timeBuffer, "%02d:%02d:%02d", hours, minutes, seconds);
  return String(timeBuffer);
}
