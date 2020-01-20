/**
 * Config
 * Copy this file into config.h and fill out the sensitive information
 */
#ifndef config_h
#define config_h

// At what level should the moisture sensor consider the water to have run out (larger number = less water)
#define WATER_OUT_LEVEL 700

// For how many microsecond intervals should the device sleep between checking whether to run the watering routine?
// Default = 3 hours = 3 * 60 * 60 * 1000000 = 10,800,000,000
#define SLEEP_DEFAULT 10800e6

// The water level sensor is only activated when required by setting this pin HIGH
#define PIN_WATER_LEVEL_POWER D4

// The water level is read on this pin
#define PIN_WATER_LEVEL A0

// This pin activates the water pump
#define PIN_PUMP D8

// This pin controlls the attached LED
#define PIN_LED D7

// This pin simply registerd whether the battery is low or not.
#define PIN_BATTERY D2

// This is the virtual pin in the Blynk App that controls the duration to run the pump for (seconds)
#define PIN_BLYNK_PUMP_DURATION V0

// This is the virtual pin in the Blynk App that displays the terminal widget
#define PIN_BLYNK_TERMINAL V1

// This is the virtual pin in the Blynk App for the Time Input Widget
#define PIN_BLYNK_RUN_TIME V2

// This is the virtual pin in the Blynk App that we write to to indicate low battery
#define PIN_BLYNK_LOW_BATTERY_LED V3

// This is the virtual pin in the Blynk App that we write to to indicate low water
#define PIN_BLYNK_LOW_WATER_LED V4

// This is the virtual pin in the Blynk App that determines whether we want push alerts or not
#define PIN_BLYNK_ALERTS_ENABLED V5

// This is the virtual pin in the Blynk App that controls whether the watering routine
// Should be run on next wake regardless of whether or not the watering routine has
// already run today.
#define PIN_BLYNK_FORCE_WATER V6

// How long should we attempt to connect to the Blynk service? (in ms)
#define BLYNK_CONNECTION_TIMEOUT 10000

// Place your Blynk Auth Token in here
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char blynkAuthToken[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#endif
