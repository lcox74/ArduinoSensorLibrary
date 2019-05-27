#ifndef ASL_HALLEFFECT_UGN3503UA_H_
#define ASL_HALLEFFECT_UGN3503UA_H_

/*
A representation of the UGN3503UA Hall effect sensor.
It would probably work with most hall effect sensors,
but I have only tested it with the UGN3503UA.
 */
class HallEffect_UGN3503UA
{
public:
	// A empty instance of the Hall effect sensor
	HallEffect_UGN3503UA () { }

	/*
	Creates a full instance of the Hall effect.
	Parameters:
		pin - The component I/O location
	 */
	HallEffect_UGN3503UA (byte pin) 
	{
		// Set the pin to INPUT.
		pinMode(pin, INPUT);

		// Record the pin location locally.
		this->pin = pin;

		// Allow the component to give propper results.
		this->componentSet = true;
	}
	
	/*
	Returns a true of false value depending on if it
	detects a magnetic field or not. The value can be
	inverted if you wired up the component in reverse 
	or just because it is handy.
	Parameters:
		invert - Inverts the value, defaults to false
	 */
	bool detect (bool invert = false) { return (digitalRead(this->pin) == HIGH && invert == false && this->componentSet) ? true : false; }

	/*
	Returns the component pin location. If it hasn't 
	been set yet then return -1.
	Returns: The pin location.
	 */
	byte getPin () { (this->componentSet) ? return pin : -1; }

	/*
	Set the components pin location. If it is less 
	than 0 or null then detect(bool) will return 
	false and getPin() will return -1.
	Parameters:
		pin - Component's I/O location
	 */
	void setPin (byte pin) 
	{
		// If the pin is invalid then don't use
		// the component.
		if (pin < 0 || pin == NULL)
		{
			this->componentSet = false;
			return;
		}

		// Sets the new pin to INPUT
		pinMode(pin, INPUT);

		// Records the new pin location
		this->pin = pin; 

		// Set the component to active...
		// that would be a better name for 
		// that.
		this->componentSet = true;
	} 

private:
	// The component location.
	byte pin;

	// Is the component setup?
	bool componentSet = false;
};

#endif //ASL_HALLEFFECT_UGN3503UA_H_