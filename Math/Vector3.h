#ifndef ASL_VECTOR3_H_
#define ASL_VECTOR3_H_

class Vector3
{
public:
	Vector3 () : x(0), y(0), z(0) { }
	Vector3 (float x1, float y1, float z1) : x(x1), y(y1), z(z1) { }

	float dot (Vector3 a) { return x * a.x + y * a.y + z * a.z; }
	Vector3 cross (Vector3 a) { return Vector3(y * a.z + z * a.y, 
											   x * a.z + z * a.x, 
											   x * a.y + y * a.x); }
	
	float magnitude () { return sqrt(dot(*this)); }
	void Normalise () { *this = normalised(); }
	Vector3 normalised () 
	{ 
		float m = magnitude(); 
		return Vector3(x / m, y / m, z / m); 
	}

	Vector3 lerp (Vector3 a, Vector3 b, float t) 
	{
		return Vector3(LERP(a.x, b.x, t), LERP(a.y, b.y, t), LERP(a.z, b.z, t));
	}
	Vector3 slerp (Vector3 a, Vector3 b, float t) 
	{
		float theta = acos(a.dot(b));
		return ( a * (float)(sin((1 - t) * theta) / sin(theta)) + b * (float)(sin(t * theta) / sin(theta)) );
	}

	inline Vector3 operator+ (Vector3 b) 	{ return Vector3(x + b.x, y + b.y, z + b.z); }
	inline Vector3 operator- (Vector3 b) 	{ return Vector3(x - b.x, y - b.y, z - b.z); }
	inline Vector3 operator* (float v)		{ return Vector3(x * v, y * v, z * v); }
	inline Vector3 operator/ (float v)		{ return Vector3(x / v, y / v, z / v); }

	String toString () { return ("( " + String(this->x) + ", " + String(this->y) + ", " + String(this->z) + " )"); }

	float x, y, z;
};

#endif //ASL_VECTOR3_H_