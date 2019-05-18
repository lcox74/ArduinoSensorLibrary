#ifndef ASL_ULTRASONICSENSOR_HCSR04_H_
#define ASL_ULTRASONICSENSOR_HCSR04_H_

class UltrasonicSensor_HCSR04
{
public:
	UltrasonicSensor_HCSR04 () { }
	UltrasonicSensor_HCSR04 (byte trig, byte echo)
	{
		pinMode(trig, OUTPUT); 	this->trigerPin = trig;
		pinMode(echo, INPUT); 	this->echoPin = echo;
	}

	int pulse () // Centimeters
	{
		clean();
		digitalWrite(this->trigerPin, HIGH);
		delayMicroseconds(10);
		clean();

		return (pulseIn(this->echoPin, HIGH) / 2) * ( 1 / 29.1545 );
	}

private:
	byte trigerPin;
	byte echoPin;

	void clean()
	{
		digitalWrite(this->trigerPin, LOW);
		delayMicroseconds(5);
	}
};

#endif //ASL_ULTRASONICSENSOR_HCSR04_H_