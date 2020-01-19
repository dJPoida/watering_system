/**
 * Config
 * Copy this file into config.h and fill out the sensitive information
 */
#ifndef config_h
#define config_h

// At what level should the moisture sensor consider the water to have run out (larger number = less water)
#define waterOutLevel 700

// For how many milliseconds should the pump run (60000 = 60 seconds)
#define pumpDuration 5000

// The water level sensor is only activated when required by setting this pin HIGH
#define PIN_WATER_LEVEL_POWER D4

// The water level is read on this pin
#define PIN_WATER_LEVEL A0

// This pin activates the water pump
#define PIN_PUMP D8

// This pin controlls the attached LED
#define PIN_LED D7

// This pin simply registered whether the battery is low or not.
#define PIN_BATTERY D2

#endif
