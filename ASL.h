#ifndef ASL_H
#define ASL_H

#ifdef ARDUINO
	#include "Arduino.h"
	#include "Print.h"
	#include <Wire.h>
#else // IF NOT ARDUINO
	#error ASL only supports Arduino!
#endif //ARDUINO

#include <math.h>

// ------------- MATH ------------- 

#define LERP(start, end, t) ((1 - t) * start + end * t)
#define CLAMP(min, max, value) ((value >= max) ? max : ((value <= min) ? min : value))

#include "Math/Vector3.h"

// ------------- Muic -------------

#include "Speaker/Notes.h"

// ------------- DEBUGGING ------------- 
#define LOG(s, newLine) Serial.begin(9600); if (newLine) Serial.println(s); else Serial.print(s)

// ------------- INBUILT LED ------------- 
#define LED_ON()     pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, HIGH)
#define LED_OFF()    pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, LOW)
#define LED_BLINK(d) pinMode(LED_BUILTIN, OUTPUT); for (int i = 0; i < d; ++i) { digitalWrite(LED_BUILTIN, HIGH); delay(d); digitalWrite(LED_BUILTIN, LOW);  delay(d); }

// ------------- COMPONENTS ------------- 
#include "Diode/Diode.h"
#include "Button/Button.h"
#include "Motor/Motor_DC.h"
#include "Magnetometer/Magnetometer_HMC5883L.h"
#include "HallEffect/HallEffect_UGN3503UA.h"
#include "UltrasonicSensor/UltrasonicSensor_HCSR04.h"
#include "MotorShield/MotorShield_L298PTWIN.h"

#endif // ASL_H