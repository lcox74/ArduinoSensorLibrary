#ifndef ASL_MOTORSHIELD_L298PTWIN_H_
#define ASL_MOTORSHIELD_L298PTWIN_H_

/*
The representation of the L298PTWIN motor shield
for the arduino.
 */
class MotorShield_L298PTWIN
{
public:
	// Create an instance of the motor shield manually
	MotorShield_L298PTWIN(byte e1 = 10, byte e2 = 11, byte m1 = 12, byte m2 = 13)
	{
		// Create motors for the pins.
		this->m1 = Motor_DC(e1, m1);
		this->m2 = Motor_DC(e2, m2);
	}

	// Create an instance of the motor shield with determined
	// motors.
	MotorShield_L298PTWIN(Motor_DC motor1, Motor_DC motor2) 
	{
		this->m1 = motor1;
		this->m2 = motor2;
	}

	/*
	Make the Motors go forward by speed s

	speed 0 = off | 1 = max and 100 = max.
	Can use 0 - 1 and 0 - 100 depending on 
	situation. Clamps the speed to those limits.
	*/
	void Forward (float s) 
	{
		this->m1.Forward(s);
		this->m2.Forward(s);
	}

	/*
	Make the Motors go backward by speed s
	
	speed 0 = off | 1 = max and 100 = max.
	Can use 0 - 1 and 0 - 100 depending on 
	situation. Clamps the speed to those limits.
	*/
	void Backward (float s) 
	{
		this->m1.Backward(s);
		this->m2.Backward(s);
	}

	// Make the Motors stop
	void Stop () 
	{
		this->m1.Forward(0);
		this->m2.Forward(0);
	}

	/*
	Set the speeds of each motor seperately.
	-100 to 100 or -1 to 1
	 */
	void setSpeeds (float ls, float rs)
	{
		if (ls < 0) this->m1.Backward(abs(ls)); else this->m1.Forward(abs(ls));
		if (rs < 0) this->m2.Backward(abs(rs)); else this->m2.Forward(abs(rs));
	}

	// Return Motor 1
	Motor_DC getMotor1 () { return this->m1; }
	// Set Motor 1
	void setMotor1 (Motor_DC m) { this->m1 = m; }

	// Return Motor 2
	Motor_DC getMotor2 () { return this->m2; }
	// Set Motor 2
	void setMotor2 (Motor_DC m) { this->m2 = m; }

private:
	Motor_DC m1; // Left (depending on motor orientation)
	Motor_DC m2; // Right (depending on motor orientation)
};

#endif //ASL_MOTORSHIELD_L298PTWIN_H_