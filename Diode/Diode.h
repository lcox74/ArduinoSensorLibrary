#ifndef ASL_DIODE_H_
#define ASL_DIODE_H_

class Diode
{
public:
	Diode () {}
	Diode (byte pin)
	{
		pinMode(pin, OUTPUT);
		this->pin = pin;
	}

	inline void On () { digitalWrite(this->pin, HIGH); }
	inline void Off () { digitalWrite(this->pin, LOW); }
	inline void Flash (int n, int wait = 100)
	{
		for (int i = 0; i < n; ++i)
		{
			On();	delay(wait);
			Off();	if (i != n - 1) delay(wait);
		}
	}

	int getPin () { return this->pin; }
	void setPin (byte pin)
	{ 
		pinMode(this->pin, INPUT); 
		pinMode(pin, OUTPUT);
		this->pin = pin;
	}

private:
	byte pin;
};

#endif //ASL_DIODE_H_