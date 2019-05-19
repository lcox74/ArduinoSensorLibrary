#ifndef ASL_BUTTON_H_
#define ASL_BUTTON_H_

class Button
{
public:
	Button(byte pin) 
	{
		pinMode(pin, INPUT);
		this->pin = pin;
	}

	bool getState (bool invert = false) { return (digitalRead(this->pin) == 1 && invert) ? false : true; }

	byte getPin () { return this->pin; }
	void setPin (byte pin) 
	{
		pinMode(pin, INPUT);
		this->pin = pin;
	}

private:
	byte pin;
};

#endif // ASL_BUTTON_H_