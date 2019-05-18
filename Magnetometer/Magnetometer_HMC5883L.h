#ifndef ASL_MAGNETOMETER_HMC5883L_H_
#define ASL_MAGNETOMETER_HMC5883L_H_

class Vector3;

class Magnetometer_HMC5883L
{
public:
	Magnetometer_HMC5883L(int address) 
	{
		this->address = address;

		Serial.begin(9600); 
		// initialise();
	}

	void initialise ()
	{
		Wire.begin();

		Wire.beginTransmission(this->address);
		Wire.write(0x0B); // Tell the HMC5883 to Continuously Measure
		Wire.write(0x01); // Set the Register
		Wire.endTransmission();

		Wire.beginTransmission(this->address);
		Wire.write(0x09); // Tell the HMC5883 to Continuously Measure
		Wire.write(0x1D); // Set the Register
		Wire.endTransmission();

    	offset = heading();
	}

	Vector3 heading ()
	{
		int x, y, z; //triple axis data

		Wire.beginTransmission(this->address);
		Wire.write(0x00); //start with register 3.
		Wire.endTransmission();

		//Read the data.. 2 bytes for each axis.. 6 total bytes
		Wire.requestFrom(this->address, 6);
		if (6 <= Wire.available()) 
		{
			x = Wire.read(); //MSB  x
			x |= Wire.read() << 8; //LSB  x
			z = Wire.read(); //MSB  z
			z |= Wire.read() << 8; //LSB z
			y = Wire.read(); //MSB y
			y |= Wire.read() << 8; //LSB y
		}

		return Vector3(x, y, z) - offset;
	}

	int getAddress () { return address; }
	void setAddress (int address) 
	{
		this->address = address;
		initialise();
	}

	Vector3 getOffset () { return offset; }
	void setOffset (Vector3 offset) { this->offset = offset; initialise(); }

private:
	Vector3 offset;
	int address;
};

#endif // ASL_MAGNETOMETER_HMC5883L_H_