# watering_system
dJPoida's automated garden watering system.

This is a simple project for activating a water pump that sits inside a small reservoir to regularly water my herbs because I'm a numpty and always seem to forget. Homemade pizza is much nicer with fresh Basil, Oregano and Chilli!

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

## Schematic
**Note:** the Wemos D1 R2 Fritzing part isn't perfect so this schematic is mostly representative.
![Schematic](https://github.com/dJPoida/watering_system/blob/master/designs/circuit%20design%20v1.0_schem.png)

## Breadboard
**Note:** the Wemos D1 R2 Fritzing part isn't perfect so this breadboard diagram is mostly representative.
![Breadboard](https://github.com/dJPoida/watering_system/blob/master/designs/circuit%20design%20v1.0_bb.png)

## Workflow
![Workflow](https://github.com/dJPoida/watering_system/blob/master/designs/workflow.png)
