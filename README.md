# dJPoidas Watering System
dJPoida's automated garden watering system.

This is a simple project for activating a water pump that sits inside a small reservoir to regularly water my herbs because I'm a numpty and always seem to forget. Homemade pizza is much nicer with fresh Basil, Oregano and Chilli!

![Hey there](https://github.com/dJPoida/watering_system/blob/master/photos/Hey%20there.jpg)
![Nozzle among the green](https://github.com/dJPoida/watering_system/blob/master/photos/Nozzle%20among%20the%20green.jpg)
![Nozzle up close](https://github.com/dJPoida/watering_system/blob/master/photos/Nozzle%20up%20close.jpg)
![Off the printer](https://github.com/dJPoida/watering_system/blob/master/photos/Off%20the%20printer.jpg)
![Electronics](https://github.com/dJPoida/watering_system/blob/master/photos/Electronics.jpg)
![Reservoir](https://github.com/dJPoida/watering_system/blob/master/photos/Reservoir.jpg)
![Reservior Lid](https://github.com/dJPoida/watering_system/blob/master/photos/Reservior%20Lid.jpg)

## Dependencies
### Arduino
The code for this project is written for the Arduino platform.
### Blynk
This project leverages the [Blynk IoT platform](https://blynk.io/) for remote management and reporting.

## Instructions
- Clone the repo
- Copy the `config_example.h` to `config.h` and populate with your appropriate config values. Specifically:
    - `blynkAuthToken[]`
    - `ssid[]`
    - `pass[]`
- Set your board config properly before uploading or the pins and flash won't work properly: 
    - LOLIN(WEMOS) D1 R2 & Mini
    - Flash Size: 4M (1M SPIFFS)
- Install Blynk on your control device (mobile / tablet) and load the control app by scanning the QR Code

## Blynk App
This is what the Blynk control app looks like
![Blynk Screenshot](https://github.com/dJPoida/watering_system/blob/master/blynk/app_screenshot.jpg)

To start with the Blynk app I created, scan this code in blynk
![Blynk App](https://github.com/dJPoida/watering_system/blob/master/blynk/app_barcode.png)

## Schematic
**Note:** the Wemos D1 R2 Fritzing part isn't perfect so this schematic is mostly representative.
![Schematic](https://github.com/dJPoida/watering_system/blob/master/designs/circuit%20design%20v1.0_schem.png)

## Breadboard
**Note:** the Wemos D1 R2 Fritzing part isn't perfect so this breadboard diagram is mostly representative.
![Breadboard](https://github.com/dJPoida/watering_system/blob/master/designs/circuit%20design%20v1.0_bb.png)

## Workflow
![Workflow](https://github.com/dJPoida/watering_system/blob/master/designs/workflow.png)

## SPIFFS Cache file
The data stored in SPIFFS is nothing complex and simply assists in the determination of next watering time.

- Line 1: Date last executed watering routine (stored as a `long` formatted `YYYYMMDD`)
- Line 2: Time of day last executed watering routine (stored as a `long` in 24hr format `HHMMSS`)
```
20200119
160212
```
The above data indicates that the watering routine was last executed at 4:02:12pm on January 19, 2020.
