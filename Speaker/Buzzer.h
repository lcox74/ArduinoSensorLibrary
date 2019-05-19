#ifndef ASL_BUZZER_H_
#define ASL_BUZZER_H_

class Buzzer
{
public:
	Buzzer(byte pin) 
	{
		pinMode(pin, OUTPUT);
		this->pin = pin;
	}
	void Play () { tone(this->pin, this->freq, this->dur); }
	void Play (int frequency, int duration) 
	{ 
		tone(this->pin, frequency, duration); 
		this->freq = frequency;
		this->dur = duration;
	}
	void Play (int note, int noteValue, int tempo)
	{
		this->freq = note;
		this->dur = (int)((float)tempo / (float)noteValue);
		tone(this->pin, this->freq, this->dur);
	}

	byte getPin () { return this->pin; }
	void setPin (byte pin) 
	{
		pinMode(this->pin, INPUT);
		pinMode(pin, OUTPUT);
		this->pin = pin;
	}

	int getFrequency () { return this->freq; }
	void setFrequency (int f) { this->freq = f; }

	int getDuration () { return this->dur; }
	void setDuration (int d) { this->dur = d; }
	void setDuration (int noteValue, int tempo) { this->dur = (int)((float)tempo / (float)noteValue); }

private:
	byte pin;
	int freq, dur;
};

#endif //ASL_BUZZER_H_