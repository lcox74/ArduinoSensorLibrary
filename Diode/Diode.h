#ifndef ASL_DIODE_H_
#define ASL_DIODE_H_

/*
Represents diodes in the electrical circuit. It also can
be used to represent other components that need to be
digitally changed on or off like Transistors and Relays.
 */
class Diode
{
public:
	/*
	Creates a base representation of the Diode, doesn't
	allow to be turned on as there is no pin set yet.
	*/
	Diode () { }

	/*
	Creates a full representation of the Diode and sets
	a I/O pin to be turned on and off.
	Parameters:
		pin - The I/O pin that the component is connected
			  to.
	*/
	Diode (byte pin)
	{
		// Set pin to OUTPUT mode
		pinMode(pin, OUTPUT);

		// Record the pin location
		this->pin = pin;

		// Allow the Diode to be turned ON and OFF
		this->componentSet = true;
	}

	/*
	These inline functions don't do anything if the
	pin hasn't been set.
	*/

	// Turns the component on. Releases a signal.
	inline void On () { if (this->componentSet) digitalWrite(this->pin, HIGH); }
	// Turns the component off. Doesn't realase a signal.
	inline void Off () { if (this->componentSet) digitalWrite(this->pin, LOW); }

	/*
	Make the component flash n times with a given delay
	in between flashes.
	Parameters:
		n    - The number of times to turn on and off
		wait - The amount of delay in milliseconds 
			   between each flash.
	 */
	inline void Flash (int n, int wait = 100)
	{
		// If the pin isn't set, don't do anything
		if (this->componentSet)
		{
			// Loop n times
			for (int i = 0; i < n; ++i)
			{
				// Turn on and stay on for the delay
				On();	delay(wait);

				// Turn off and stay off for the delay.
				// But don't delay on the last off.
				Off();	if (i != n - 1) delay(wait);
			}
		}
	}

	/*
	Returns the I/O pin for the component. Returns -1 if
	no pin is set.
	Returns: The components pin location.
	 */
	int getPin () { return (this->componentSet) ? this->pin : -1; }

	/*
	Sets a new pin the component is at.
	Parameter:
		pin - The new pin location
	 */
	void setPin (byte pin)
	{ 
		// If the pin is invalid, then make the component
		// not set to anything.
		if (pin < 0 || pin == NULL) 
		{
			this->componentSet = false;
			return;
		}

		// Set the old pin location to it's default state.
		pinMode(this->pin, INPUT); 

		// Set the new pin to OUTPUT.
		pinMode(pin, OUTPUT);

		// Record the pin location.
		this->pin = pin;

		// Set the pin to be turned on and off.
		this->componentSet = true;
	}

private:
	// The component I/O location
	byte pin;

	// The component limiter. If false then it can't do
	// anything.
	bool componentSet = false;
};

#endif //ASL_DIODE_H_