#ifndef ASL_MAGNETOMETER_HMC5883L_H_
#define ASL_MAGNETOMETER_HMC5883L_H_

#ifdef ARDUINO
	// Required for I2C
	#include <Wire.h>
#else // IF NOT ARDUINO
	#error ASL only supports Arduino!
#endif //ARDUINO

// Pre delcare the Vector3 class
class Vector3;

/*
Represents the Magnetometer HMC5883L compass. 
Because ofsome weird reason, the HMC5883L is 
actually a QMC5883L. So if you have a QMC5883L 
then this will work for that too.
 */
class Magnetometer_HMC5883L
{
public:
	/*
	Creates an instance of the magnetometer. The
	magnetometer uses I2C so the address will need
	to be found for the Magnetometer using a I2C
	address finder. Usually defaults to 0x0D.
	Parameters:
		address - The I2C address of the component
	 */
	Magnetometer_HMC5883L(int address) { this->address = address; }

	/*
	Initialise the magnetometer. Will neet to be
	called in the setup() function on the arduino.
	This sets up the marnetometer for use and creates
	a offset for it.
	 */
	void initialise ()
	{
		// Begin the I2C connection
		Wire.begin();

		// Byte 1
		Wire.beginTransmission(this->address);
		Wire.write(0x0B); // Set to continuously measure
		Wire.write(0x01); // Set register A
		Wire.endTransmission();

		// Byte 2
		Wire.beginTransmission(this->address);
		Wire.write(0x09); // Set to continuously measure
		Wire.write(0x1D); // Set register B
		Wire.endTransmission();

		// Create an offset
    	offset = heading();
	}

	/*
	Gets the vector from the components location to
	the closest and strongest magnetic field.
	Returns: A vector of the nearest megnetic field.
	 */
	Vector3 heading ()
	{
		int x, y, z;

		// Send a byte of data to register C to prepare to
		// get the data output.
		Wire.beginTransmission(this->address);
		Wire.write(0x00);
		Wire.endTransmission();

		// Request the data from the component.
		// 6 Bytes of data. 2 for each axis.
		Wire.requestFrom(this->address, 6);
		if (6 <= Wire.available()) 
		{
			// Read the X data output from the LSB and MSB Registers
			x = Wire.read();
			x |= Wire.read() << 8;
			// Read the Z data output from the LSB and MSB Registers
			z = Wire.read();
			z |= Wire.read() << 8;
			// Read the Y data output from the LSB and MSB Registers
			y = Wire.read();
			y |= Wire.read() << 8;
		}

		// Return the vector minus the offset
		return Vector3(x, y, z) - offset;
	}

	// Returns the set I2C address of the component
	int getAddress () { return address; }

	/*
	Set the new address of the component if it needs
	to be changed.
	Parameters:
		address - The new I2C address
	 */
	void setAddress (int address) 
	{
		// Record the new address
		this->address = address;

		// Re-initialise
		initialise();
	}

	// Returns the offset
	Vector3 getOffset () { return offset; }

	// Set the offset manually
	void setOffset (Vector3 offset) { this->offset = offset; }

	// Set the offset automatically
	void setOffset () { this->offset = heading(); }

private:
	// The offset of the direction to the greatest
	// magnetic field.
	Vector3 offset;

	// The I2C address location of the component.
	int address;
};

#endif // ASL_MAGNETOMETER_HMC5883L_H_