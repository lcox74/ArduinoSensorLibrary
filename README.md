# ArduinoSensorLibrary (ASL)
ASL is a library that makes it easier to implement sensors and other components to the [Arduino Uno r3](https://store.arduino.cc/usa/arduino-uno-rev3). This was made to simplify large chuncks of code into something more readable and English for the rest of my team can understand what the arduino code does.

## Supported Components
- [Hall Effect Sensor UGN3503UA](https://www.jaycar.com.au/medias/sys_master/images/9229136101406/ZD1902-dataSheetMain.pdf)
- [Magnetometer HMC5883L](https://cdn-shop.adafruit.com/datasheets/HMC5883L_3-Axis_Digital_Compass_IC.pdf)
- [Motor Shield L298P-TWIN](http://image.dfrobot.com/image/data/DRI0009/L298N%20datasheet.pdf)
- [Ultrasonic Sensor HC-SR04](https://www.electroschematics.com/wp-content/uploads/2013/07/HCSR04-datasheet-version-1.pdf)
- Diodes
- DC Motors

### Component Notes
You can use the Diodes object for other things such as transistors and relays or anything that requires 1 selector pin and only has a **On** or **Off** state.

## How to use?
1. `git clone https://github.com/lcox74/ArduinoSensorLibrary` into your Arduino library folder, typically found in your Documents folder.
2. Open the Arduino IDE.
3. On your toolbar click `Sketch->Include Library->ArduinoSensorLibrary` it might have `-master` at the end of it depending on how you cloned it.
4. If it worked then `#include <ASL.h>` would have appeared on top of your file.
5. You're set to go.

If the library didn't show up in your Include Library then you can put the ArduinoSensorLibrary folder into your solution folder. The folder your script is saved, the folder that has {your script name}.ino in it. Then to include it into your script put `#include "ArduinoSensorLibrary/ASL.h"` at the top of your file.
