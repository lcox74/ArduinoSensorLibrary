#ifndef ASL_MOTORSHIELD_L298PTWIN_H_
#define ASL_MOTORSHIELD_L298PTWIN_H_

class MotorShield_L298PTWIN
{
public:
	MotorShield_L298PTWIN(byte e1 = 10, byte e2 = 11, byte m1 = 12, byte m2 = 13)
	{
		this->m1 = new Motor_DC(e1, m1);
		this->m2 = new Motor_DC(e2, m2);
	}
	MotorShield_L298PTWIN(Motor_DC motor1, Motor_DC motor2) 
	{
		this->m1 = &motor1;
		this->m2 = &motor2;
	}
	~MotorShield_L298PTWIN()
	{
		delete this->m1;
		delete this->m2;
	}

	void Forward (float s) 
	{
		this->m1->Forward(s);
		this->m2->Forward(s);
	}
	void Backward (float s) 
	{
		this->m1->Backward(s);
		this->m2->Backward(s);
	}

	void Stop () 
	{
		this->m1->Forward(0);
		this->m2->Forward(0);
	}

	void setSpeeds (float ls, float rs)
	{
		if (ls < 0) this->m1->Backward(abs(ls)); else this->m1->Forward(abs(ls));
		if (rs < 0) this->m2->Backward(abs(rs)); else this->m2->Forward(abs(rs));
	}

	Motor_DC getMotor1 () { return *this->m1; }
	void setMotor1 (Motor_DC m) { this->m1 = &m; }

	Motor_DC getMotor2 () { return *this->m2; }
	void setMotor2 (Motor_DC m) { this->m2 = &m; }

private:
	Motor_DC *m1; // Left (depending on motor orientation)
	Motor_DC *m2; // Right (depending on motor orientation)
};

#endif //ASL_MOTORSHIELD_L298PTWIN_H_