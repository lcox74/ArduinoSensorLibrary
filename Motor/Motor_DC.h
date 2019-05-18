#ifndef ASL_MOTOR_DC_H_
#define ASL_MOTOR_DC_H_

#define FORWARD LOW
#define BACKWARD HIGH

class Motor_DC
{
public:
	Motor_DC ();
	Motor_DC (byte s, byte dir) 
	{
		pinMode(s, OUTPUT); 	this->speed = s;
		pinMode(dir, OUTPUT);	this->direction = dir;
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
};

#endif //ASL_MOTOR_DC_H_