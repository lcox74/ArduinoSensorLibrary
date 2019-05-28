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

	// Set the direction, FORWARD or BACKWARD
	// FORWARD = HIGH = 1
	// BACKWARD = LOW = 0
	inline void setDirection (int direction) { digitalWrite(this->direction, direction); }

	/*
	Set the speed 0 = off
	1 = max and 100 = max
	Can use 0 - 1 and 0 - 100 depending on 
	situation. Clamps the speed to those limits.
	*/
	inline void setSpeed (float s)
	{ 
		// If 0 - 1
	    if (s <= 1 && s > 0)
			analogWrite(this->speed, LERP(0, 255, CLAMP(0, 1, s))); 
	    else // 0 - 100
			analogWrite(this->speed, LERP(0, 255, CLAMP(0, 100, s)/100)); 
	}

	// Make the motor go forward a certain speed.
	inline void Forward (float s) 	{ setDirection(FORWARD); setSpeed(s); }
	// Make the motor go backward a certain speed.
	inline void Backward (float s)	{ setDirection(BACKWARD); setSpeed(s); }

	// Get the speed pin for this motor. -1 if not set.
	byte getSpeed () { return (this->componentSet) ? this->speed : -1; }

	/*
	Set the speed I/O pin for the motor.
	If the pin is invalid then it makes 
	the motor inactive.
 	*/
	void setSpeed (byte pin) 
	{
		// If not valid set to -1 and make inactive
		if (pin < 0 || pin == NULL)
		{
			componentSet = false;
			setTemp = 0;
			this->speed = -1;
			return;
		}

		// Reset the old pin mode
		pinMode(this->speed, INPUT);

		// Set the new pin mode
		pinMode(pin, OUTPUT);

		// Record the new pin location
		this->speed = pin;

		// If the componentSet is false and both the
		// pins have been set then make the motor active.
		if (componentSet == false && setTemp == 0)
			setTemp = 1;
		else if (componentSet == false && setTemp == 1)
			componentSet = true;
	}

	// Get the speed pin for this motor. -1 if not set.
	byte getDirection () { return (this->componentSet) ? this->direction : -1; }

	/*
	Set the direction I/O pin for the motor.
	If the pin is invalid then it makes 
	the motor inactive.
 	*/
	void setDirection (byte pin) 
	{
		// If not valid set to -1 and make inactive
		if (pin < 0 || pin == NULL)
		{
			componentSet = false;
			setTemp = 0;
			this->direction = -1;
			return;
		}

		// Reset the old pin mode
		pinMode(this->direction, INPUT);

		// Set the new pin mode
		pinMode(pin, OUTPUT);
		
		// Record the new pin location
		this->direction = pin;

		// If the componentSet is false and both the
		// pins have been set then make the motor active.
		if (componentSet == false && setTemp == 0)
			setTemp = 1;
		else if (componentSet == false && setTemp == 1)
			componentSet = true;
	}
private:
	// The pin location for the motor
	byte speed; 
	byte direction;

	// Is the component setup?
	bool componentSet = false;
	int setTemp = 0;
};

#endif //ASL_MOTOR_DC_H_