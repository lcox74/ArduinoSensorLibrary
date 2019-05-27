#ifndef ASL_VECTOR3_H_
#define ASL_VECTOR3_H_

// Pre define linear interpolation
#define LERP(start, end, t) ((1 - t) * start + end * t)

/*
The representation of a 3d vector.
 */
class Vector3
{
public:
	// A empty vector instance.
	Vector3 () : x(0), y(0), z(0) { }

	/*
	A vector instance with given values (x, y, z).
	Parameters:
		x1 - The x coord.
		y1 - The y coord.
		z1 - The z coord.
	 */
	Vector3 (float x1, float y1, float z1) : x(x1), y(y1), z(z1) { }

	/*
	Returns the dot product of this vector to another 
	vector.
	Parameters:
		a - The other vector to project onto.
	Returns: The dot product of this vector to vector 'a'
	 */
	float dot (Vector3 a) { return x * a.x + y * a.y + z * a.z; }

	/*
	Returns the cross product of this vector to another
	vector.
	Parameters:
		a - The other vector.
	Returns: The cross product of both vectors.
	 */
	Vector3 cross (Vector3 a) { return Vector3(y * a.z + z * a.y, 
											   x * a.z + z * a.x, 
											   x * a.y + y * a.x); }
	
	/*
	Returns the magnitude of this vector using
	Pythagoras Theroem
	*/
	float magnitude () { return sqrt(dot(*this)); }

	// Normalise the vector
	void Normalise () { *this = normalised(); }

	/*
	Return what the vector would be if it was
	normalised.
	Returns: The normalised vector.
	 */
	Vector3 normalised () 
	{ 
		// Getting the magnitude of the vector
		float m = magnitude(); 

		// Creating a new vector with the values
		// divided by the magnitude to normalise.
		return Vector3(x / m, y / m, z / m); 
	}

	/*
	Returns the angle between two vectors
	in radians.
	Parameters:
		a - The other vector
	Returns: The angle between the vectors.
	 */
	float angle (Vector3 a) 
	{
		// Getting the projection of this vector 
		// to vector a.
		float dot = a.dot(*this);

		// Getting the magnitude of both vectors
		float mag = magnitude() * a.magnitude();

		// return the arc cos of the dot / magnitude
		// of both vectors.
		return acosf(dot / mag);
	}

	/*
	Returns a new vector that has been linearly
	interpolated between two vectors by a given
	percent.
	Parameters:
		a - The starting vector
		b - The ending vector
		t - The percent between the two vectors
			to be at (0 - 1). 0 = starting vector. 
			1 = ending vector.
	 */
	Vector3 Lerp (Vector3 a, Vector3 b, float t) 
	{
		// Linerally interpolating each value and 
		// returning the new vector.
		return Vector3(LERP(a.x, b.x, t), LERP(a.y, b.y, t), LERP(a.z, b.z, t));
	}

	/*
	Returns a new vector that has been sphericaly
	linear interpolated between two vectors by a
	given percent. "https://en.wikipedia.org/wiki/Slerp"
	Parameters:
		a - The starting vector
		b - The ending vector
		t - The percent between the two vectors
			to be at (0 - 1). 0 = starting vector. 
			1 = ending vector.
	 */
	Vector3 Slerp (Vector3 a, Vector3 b, float t) 
	{
		// Get the projection of both vectors.
		float dot = a.dot(b);

		// If the dot is negative then the slerp
		// wont take the shorter both. So by 
		// inversing the dot and vector b it solves
		// the problem.
		if (dot < 0.0f)
		{
			dot = -dot;
			b = b * -1;
		}

		// arc cos is only able to be from 
		// -1 to 1 otherwise there is a math 
		// error.
		if (dot > 0.9995f)
			return Lerp(a, b, t);

		float theta_0 = acosf(dot);
		float theta = theta_0 * t;
		float sin_theta = sin(theta);
		float sin_theta_0 = sin(theta_0);

		float s0 = cos(theta) - dot * sin_theta / sin_theta_0;
		float s1 = sin_theta / sin_theta_0;

		// Return the vector with the shortest path
		// from a to b by t.
		return (a * s0) + (b * s1);
	}

	// Operator Overloading
	inline Vector3 operator+ (Vector3 b) 	{ return Vector3(x + b.x, y + b.y, z + b.z); }
	inline Vector3 operator- (Vector3 b) 	{ return Vector3(x - b.x, y - b.y, z - b.z); }
	inline Vector3 operator* (float v)		{ return Vector3(x * v, y * v, z * v); }
	inline Vector3 operator/ (float v)		{ return Vector3(x / v, y / v, z / v); }

	/*
	Returns the vector as a string representation
	in the format of (x, y, z).
	Returns: The vector as a string
	 */
	String toString () { return ("( " + String(this->x) + ", " + String(this->y) + ", " + String(this->z) + " )"); }

	// The vectors values.
	float x, y, z;
};

#endif //ASL_VECTOR3_H_