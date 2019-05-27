#ifndef ASL_BUTTON_H_
#define ASL_BUTTON_H_

/*
Represents button components in a electrical circuit. The button
class can also be used to represent any component that has a single
I/O pin requirement and a digital on and off read. Such as switches.
*/
class Button
{
public:
	/*
	Creates an instance of the Button class. Must have a pin to 
	set.
	Parameter:
		pin - The I/O pin location on the arduino the component
			  is conected to.
	*/
	Button(byte pin) 
	{
		// Sets the pin on the arduino to INPUT
		pinMode(pin, INPUT);

		// Record the pin to the class so it can re-use it.
		this->pin = pin;
	}

	/*
	Returns the state of the component. 
			1 for ON 
			0 for OFF
	Returns: Button state (1 or 0)
	 */
	int getState () { return (digitalRead(this->pin) == 1) ? 0 : 1; }

	/*
	Returns the current I/O pin the component is set to.
	Returns: The components connected pin.
	 */
	byte getPin () { return this->pin; }

	/*
	Changes the pin the component is connected to.
	Parameter:
		pin - The new I/O pin location the component is.
	 */
	void setPin (byte pin) 
	{
		// Sets the new pin to INPUT mode and records it.
		pinMode(pin, INPUT);
		this->pin = pin;
	}

private:
	// The I/O pin is located at.
	byte pin;
};

#endif // ASL_BUTTON_H_