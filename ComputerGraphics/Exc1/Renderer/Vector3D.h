#pragma once

class Vector3D
{
public:
	float x, y, z;

	// Constructors
	Vector3D();
	Vector3D(float x, float y, float z);


	const Vector3D operator+(const float rhs) const;
	const Vector3D operator-(const float rhs) const;
	const Vector3D operator+(const Vector3D rhs) const;
	const Vector3D operator-(const Vector3D rhs) const;



	// * operator for multiplying with a scalar (vector * scalar)
	const Vector3D operator * (const float rhs) const;

	// * operator for multiplying with a scalar (scalar * vector)
	friend Vector3D operator * (const float rhs, const Vector3D&);

	// / operator for dividing by a scalar
	const Vector3D operator / (const float rhs) const;

	// += operator
	Vector3D& operator += (const Vector3D& rhs);

	// -= operator
	Vector3D& operator -= (const Vector3D& rhs);

	// *= operator (scalar)
	Vector3D& operator *= (const float rhs);

	// /= operator (scalar)
	Vector3D& operator /= (const float rhs);

	// unary - operator
	const Vector3D operator - () const;

	// returns the length of the vector
	float length() const;

	// computes the dot product of this and another 3 component vector
	float dot(const Vector3D& rhs) const;

	// computes the cross product of this and another 3 component vector
	const Vector3D cross(const Vector3D& rhs) const;

	// returns a normalized version of this vector
	const Vector3D normalized() const;
};