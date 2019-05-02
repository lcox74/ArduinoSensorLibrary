#ifndef MINE_LIBRARY_H
#define MINE_LIBRARY_H

#ifdef ARDUINO
	#include "Arduino.h"
	#include "Print.h"
	#include <Wire.h>
#endif

// -------------------- DEFINES --------------------
#define lerp(start, end, t) ((1 - t) * start + end * t)
#define clamp(min, max, value) ((value >= max) ? max : ((value <= min) ? min : value))

class Vector3
{
public:
	Vector3 () : x(0), y(0), z(0) {}
	Vector3 (float x1, float y1, float z1) : x(x1), y(y1), z(z1) {}

	float dot (Vector3 a) { return x * a.x + y * a.y + z * a.z; }
	Vector3 cross (Vector3 a) { return Vector3(y * a.z + a.y * z, x * a.z + z * a.x, x * a.y + y * a.x); }
	float magnitude () { return sqrt(dot(*this)); }
	Vector3 normalised () { float m = magnitude(); return Vector3(x / m, y / m, z / m); }
	void Normalise () { *this = normalised(); }

	Vector3 operator+ (Vector3 b) { return Vector3(x + b.x, y + b.y, z + b.z); }
	Vector3 operator- (Vector3 b) { return Vector3(x - b.x, y - b.y, z - b.z); }
	Vector3 operator* (float v) { return Vector3(x * v, y * v, z * v); }
	Vector3 operator/ (float v) { return Vector3(x / v, y / v, z / v); }

	String toString () { return ("( " + String(this->x) + ", " + String(this->y) + ", " + String(this->z) + " )"); }

	float x, y, z;
};

// -------------------- Hall Effect Sensor --------------------
class HallEffectSensor
{
public:
	HallEffectSensor (byte pin = 2) { pinMode(pin, INPUT); this->pin = pin; }
	bool detect () { return (digitalRead(this->pin) == HIGH) ? false : true; }

	byte pin;
};

// -------------------- Ultra Sonic Sensor --------------------
class UltrasonicSensor
{
public:
	UltrasonicSensor (byte trig, byte echo)
	{
		pinMode(trig, OUTPUT); this->trigger = trig;
		pinMode(echo, INPUT); this->echo = echo;
	}
	int pulse () // Returns distance in cm
	{
		clean();
		digitalWrite(this->trigger, HIGH);
		delayMicroseconds(10);
		clean();

		return (pulseIn(this->echo, HIGH) / 2) * ( 1 / 29.1545 );
	}
	void clean () { digitalWrite(this->trigger, LOW); delayMicroseconds(5); }

	byte trigger, echo;
};

// -------------------- Motor --------------------
#define FORWARD LOW
#define BACKWARD HIGH

class MotorDC
{
public:
  MotorDC () {}
	MotorDC (byte speed, byte direction)
	{
		pinMode(speed, OUTPUT); this->speed = speed;
		pinMode(direction, OUTPUT); this->direction = direction;
	}
	void setDirection (int direction) { digitalWrite(this->direction, direction); }
	void setSpeed (float s) 
	{ 
    if (s <= 1 && s > 0)
	    analogWrite(this->speed, lerp(0, 255, clamp(0, 1, s))); 
    else
      analogWrite(this->speed, lerp(0, 255, clamp(0, 100, s)/100)); 
	}

  void Forward (float s) { setDirection(FORWARD); setSpeed(s); }
  void Backward (float s) { setDirection(BACKWARD); setSpeed(s); }

	byte speed, direction;
};

// -------------------- DC Motor Controller --------------------
class MotorControllerDC
{
public:
  MotorControllerDC (MotorDC left, MotorDC right)
  {
    this->left = left;
    this->right = right;
  }

  void Stop () { left.Forward(0); right.Forward(0); }

  void Forward (float s) 		{ left.Forward(s); 	right.Forward(s); 	}
  void Backward (float s) 	{ left.Backward(s); right.Backward(s); 	}
  void turnLeft (float s) 	{ left.Backward(s); right.Forward(s); 	}
  void turnRight (float s) 	{ left.Forward(s); 	right.Backward(s);	}

  void setSpeeds (float ls, float rs) 
  {
		if (ls < 0) left.Backward(abs(ls)); else left.Forward(abs(ls));
		if (rs < 0) right.Backward(abs(rs)); else right.Forward(abs(rs));
  }

  MotorDC left, right;
};

// -------------------- Relay --------------------
class Relay
{
public:
	Relay (byte pin)
	{
		pinMode(pin, OUTPUT); this->pin = pin;
		this->active = false;
	}
	void toggle ()
	{
		this->active = !this->active;
		digitalWrite(this->pin, (this->active) ? HIGH : LOW);
	}
	void setSwitch (bool mode) { digitalWrite(this->pin, (mode) ? HIGH : LOW); }
	bool getState () { return active; }

	byte pin;
private:
	bool active;
};

// -------------------- Magnetometer --------------------
class Magnetometer
{
public:
	Magnetometer (int addr = 0x0D) { this->address = addr; }
	void init ()
	{
		Wire.begin();

		Wire.beginTransmission(this->address); //start talking
		Wire.write(0x0B); // Tell the HMC5883 to Continuously Measure
		Wire.write(0x01); // Set the Register
		Wire.endTransmission();

		Wire.beginTransmission(this->address); //start talking
		Wire.write(0x09); // Tell the HMC5883 to Continuously Measure
		Wire.write(0x1D); // Set the Register
		Wire.endTransmission();

    offSet = directionToFerrousMetal();
	}
	Vector3 directionToFerrousMetal ()
	{
		int x, y, z; //triple axis data

		Wire.beginTransmission(this->address);
		Wire.write(0x00); //start with register 3.
		Wire.endTransmission();

		//Read the data.. 2 bytes for each axis.. 6 total bytes
		Wire.requestFrom(this->address, 6);
		if (6 <= Wire.available()) 
		{
			x = Wire.read(); //MSB  x
			x |= Wire.read() << 8; //LSB  x
			z = Wire.read(); //MSB  z
			z |= Wire.read() << 8; //LSB z
			y = Wire.read(); //MSB y
			y |= Wire.read() << 8; //LSB y
		}

		return Vector3(x - offSet.x, y - offSet.y, z - offSet.z).normalised();
	}

  Vector3 offSet;
	int address;
};

// -------------------- LED Diodes --------------------
class Diode
{
public:
  Diode (byte pin) { pinMode(pin, OUTPUT); this->pin = pin; }
  void ON () { digitalWrite(this->pin, HIGH); }
  void OFF () { digitalWrite(this->pin, LOW); }
  void FLASH (int n, int wait = 100) 
  {
    for (int i = 0; i < n; i++)
    {
      ON();
      delay(wait);
      OFF();
      if (i != n - 1)
        delay(wait);  
    }
  }
  
  byte pin;
};

// -------------------- Inbuilt LED --------------------

#define LED_ON()     pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, HIGH)
#define LED_OFF()    pinMode(LED_BUILTIN, OUTPUT); digitalWrite(LED_BUILTIN, LOW)
#define LED_BLINK(d) pinMode(LED_BUILTIN, OUTPUT);\
                     digitalWrite(LED_BUILTIN, HIGH); delay(d);\
										digitalWrite(LED_BUILTIN, LOW);  delay(d); 

#endif //MINE_LIBRARY_H
