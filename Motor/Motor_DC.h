#ifndef ASL_MOTOR_DC_H_
#define ASL_MOTOR_DC_H_

// Pre defines Math
#define LERP(start, end, t) ((1 - t) * start + end * t)
#define CLAMP(min, max, value) ((value >= max) ? max : ((value <= min) ? min : value))

// Pre defines to make things look better
#define FORWARD LOW
#define BACKWARD HIGH

/*
The representation of a DC Motor set up for
the MotorShield_L298PTWIN.
*/
class Motor_DC
{
public:
	// Create an empty DC Motor instance
	Motor_DC () { }

	/*
	Create an DC Motor instance from a given
	speed and direction.
	Parameters:
		s -   The pin for speed (e1 or e2 eg.)
		dir - The pin for direction (m1 or m2 eg.)
	 */
	Motor_DC (byte s, byte dir) 
	{
		// Set the pin modes to OUTPUT and record
		// their pin locations.
		pinMode(s, OUTPUT); 	this->speed = s;
		pinMode(dir, OUTPUT);	this->direction = dir;

		// Set component as setup
		this->componentSet = true;
	}

	inline void setDirection (int direction) { digitalWrite(this->direction, direction); }
	inline void setSpeed (float s)
	{ 
	    if (s <= 1 && s > 0)
			analogWrite(this->speed, LERP(0, 255, CLAMP(0, 1, s))); 
	    else
			analogWrite(this->speed, LERP(0, 255, CLAMP(0, 100, s)/100)); 
	}

	inline void Forward (float s) 	{ setDirection(FORWARD); setSpeed(s); }
	inline void Backward (float s)	{ setDirection(BACKWARD); setSpeed(s); }

	byte getSpeed () { return this->speed; }
	void setSpeed (byte pin) 
	{
		pinMode(this->speed, INPUT);
		pinMode(pin, OUTPUT);
		this->speed = pin;
	}

	byte getDirection () { return this->direction; }
	void setDirection (byte pin) 
	{
		pinMode(this->direction, INPUT);
		pinMode(pin, OUTPUT);
		this->direction = pin;
	}
private:
	byte speed; 
	byte direction;

	// Is the component setup?
	bool componentSet = false;
};

#endif //ASL_MOTOR_DC_H_