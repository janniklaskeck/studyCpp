#pragma once

class Vector2
{
public:

	Vector2();
	Vector2(float _X, float _Y);
	Vector2(const Vector2& Other);

	float X;
	float Y;

	float Length();
	float LengthSquared();
	void Normalize();

	Vector2& operator=(const Vector2& Other);

	Vector2& operator+=(const Vector2& Other);
	Vector2& operator-=(const Vector2& Other);
	Vector2& operator*=(const Vector2& Other);
	Vector2& operator/=(const Vector2& Other);

	Vector2& operator+=(const float Scalar);
	Vector2& operator-=(const float Scalar);
	Vector2& operator*=(const float Scalar);
	Vector2& operator/=(const float Scalar);

	bool operator==(const Vector2& Other);
	bool operator!=(const Vector2& Other);

	~Vector2();

};

inline Vector2 operator+(Vector2 Lhs, const Vector2& Rhs)
{
	Lhs += Rhs;
	return Lhs;
}
inline Vector2 operator-(Vector2 Lhs, const Vector2& Rhs)
{
	Lhs -= Rhs;
	return Lhs;
}
inline Vector2 operator*(Vector2 Lhs, const Vector2& Rhs)
{
	Lhs *= Rhs;
	return Lhs;
}
inline Vector2 operator/(Vector2 Lhs, const Vector2& Rhs)
{
	Lhs /= Rhs;
	return Lhs;
}

inline Vector2 operator+(Vector2 Lhs, const float& Rhs)
{
	Lhs += Rhs;
	return Lhs;
}
inline Vector2 operator-(Vector2 Lhs, const float& Rhs)
{
	Lhs -= Rhs;
	return Lhs;
}
inline Vector2 operator*(Vector2 Lhs, const float& Rhs)
{
	Lhs *= Rhs;
	return Lhs;
}
inline Vector2 operator/(Vector2 Lhs, const float& Rhs)
{
	Lhs /= Rhs;
	return Lhs;
}

inline Vector2 operator+(const float& Rhs, Vector2 Lhs)
{
	Lhs += Rhs;
	return Lhs;
}
inline Vector2 operator-(const float& Rhs, Vector2 Lhs)
{
	Lhs -= Rhs;
	return Lhs;
}
inline Vector2 operator*(const float& Rhs, Vector2 Lhs)
{
	Lhs *= Rhs;
	return Lhs;
}
inline Vector2 operator/(const float& Rhs, Vector2 Lhs)
{
	Lhs /= Rhs;
	return Lhs;
}