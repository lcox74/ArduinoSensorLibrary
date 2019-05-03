#ifndef ASL_HALLEFFECT_UGN3503UA_H_
#define ASL_HALLEFFECT_UGN3503UA_H_

class HallEffect_UGN3503UA
{
public:
	HallEffect_UGN3503UA () {}
	HallEffect_UGN3503UA (byte pin) 
	{
		pinMode(pin, INPUT);
		this->pin = &pin;
	}

	~HallEffect_UGN3503UA () { delete this->pin; }
	
	bool detect (bool invert = false) { return (digitalRead(*this->pin) == HIGH && invert == false) ? true : false; }

	byte getPin () { return *pin; }
	void setPin (byte pin) 
	{
		pinMode(pin, INPUT);
		this->pin = &pin; 
	} 

private:
	byte *pin;
};

#endif //ASL_HALLEFFECT_UGN3503UA_H_