#ifndef ASL_BUZZER_H_
#define ASL_BUZZER_H_

#include "Notes.h"

/*
The representation of a buzzer in a electrical circuit.
 */
class Buzzer
{
public:
	// Create an instance of the buzzer with a given pin.
	Buzzer(byte pin) 
	{
		// Set the pin to OUTPUT
		pinMode(pin, OUTPUT);
		this->pin = pin;

		// Seting a default frequency and duration
		this->freq = 1000;
		this->dur = 1000;
	}

	// Play the default tone
	void Play () { tone(this->pin, this->freq, this->dur); }

	/*
	Play a tone from a given frequency and duration in milliseconds.
	Store the frequency and duration for a later use of
	Play().
	 */
	void Play (int frequency, int duration) 
	{ 
		tone(this->pin, frequency, duration); 
		this->freq = frequency;
		this->dur = duration;
	}

	/*
	Play a tone from a note, noteValue and tempo.
	Frequency = Note frequency
	Duration = tempo / noteValue
	Store for later use of Play().
	 */
	void Play (int note, int noteValue, int tempo)
	{
		this->freq = note;
		this->dur = (int)((float)tempo / (float)noteValue);
		tone(this->pin, this->freq, this->dur);
	}

	// Return the component I/O pin location.
	byte getPin () { return this->pin; }

	// Set the component to a new pin location.
	void setPin (byte pin) 
	{
		// Reset the old pin
		pinMode(this->pin, INPUT);
		
		// Set the new pin
		pinMode(pin, OUTPUT);
		this->pin = pin;
	}

	// Return the frequency
	int getFrequency () { return this->freq; }
	// Set the frequency
	void setFrequency (int f) { this->freq = f; }

	// Return the duration
	int getDuration () { return this->dur; }
	// Set the duration in milliseconds.
	void setDuration (int d) { this->dur = d; }
	// Set the duration with a noteValue and Tempo
	void setDuration (int noteValue, int tempo) { this->dur = (int)((float)tempo / (float)noteValue); }

private:
	// The component pin location
	byte pin;

	// The stored frequency and duration
	int freq, dur;
};

#endif //ASL_BUZZER_H_