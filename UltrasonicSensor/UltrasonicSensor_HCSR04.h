#ifndef ASL_ULTRASONICSENSOR_HCSR04_H_
#define ASL_ULTRASONICSENSOR_HCSR04_H_

/*
The representation of the HCSR04 ultrasonic sensor
 */
class UltrasonicSensor_HCSR04
{
public:
	// Create a empty ultrasonic sensor instance
	UltrasonicSensor_HCSR04 () { }

	// Create a ultrasonic sensor instance with pins
	UltrasonicSensor_HCSR04 (byte trig, byte echo)
	{
		// Set pin modes to the respected OUTPUT and INPUT
		// modes.
		pinMode(trig, OUTPUT); 	this->trigerPin = trig;
		pinMode(echo, INPUT); 	this->echoPin = echo;

		// Set the component as has been setup.
		this->componentSet = true;
	}

	/*
	Returns the distance given from the ultrasonic sensor
	in centimeters. If the component hasn't been setup then
	return -1.
	*/
	int pulse ()
	{
		// Check if set up
		if (this->componentSet == false)
			return -1;

		// Clean the trigger pin
		clean();

		// Send a short 10 millisecond pulse
		digitalWrite(this->trigerPin, HIGH);
		delayMicroseconds(10);
		
		// Clean the trigger pin
		clean();

		// Return the distance in centimeters
		// (time / 2) * (speed of sound in centimeters)
		return (pulseIn(this->echoPin, HIGH) / 2) * ( 1 / 29.1545 );
	}

private:
	// Component I/O pin locations
	byte trigerPin;
	byte echoPin;

	// Is the component setup?
	bool componentSet = false;

	// Clean the trigger pin by turning off the signal for 5 microseconds.
	// Requires 5 or more microseconds to clean.
	void clean()
	{
		digitalWrite(this->trigerPin, LOW);
		delayMicroseconds(5);
	}
};

#endif //ASL_ULTRASONICSENSOR_HCSR04_H_