#ifndef ASL_MAGNETOMETER_HMC5883L_H_
#define ASL_MAGNETOMETER_HMC5883L_H_

class Vector3;

class Magnetometer_HMC5883L
{
public:
	Magnetometer_HMC5883L(int address) { this->address = address; }

	void initialise ()
	{
		Wire.begin();

		Wire.beginTransmission(this->address);
		Wire.write(0x0B);
		Wire.write(0x01);
		Wire.endTransmission();

		Wire.beginTransmission(this->address);
		Wire.write(0x09);
		Wire.write(0x1D);
		Wire.endTransmission();

    	offset = heading();
	}

	Vector3 heading ()
	{
		int x, y, z;

		Wire.beginTransmission(this->address);
		Wire.write(0x00);
		Wire.endTransmission();

		Wire.requestFrom(this->address, 6);
		if (6 <= Wire.available()) 
		{
			x = Wire.read();
			x |= Wire.read() << 8;
			z = Wire.read();
			z |= Wire.read() << 8;
			y = Wire.read();
			y |= Wire.read() << 8;
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
	void setOffset (Vector3 offset) { this->offset = offset; }
	void setOffset () { this->offset = heading(); }

private:
	Vector3 offset;
	int address;
};

#endif // ASL_MAGNETOMETER_HMC5883L_H_