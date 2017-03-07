#include "Vector2.hpp"
#include <algorithm>

Vector2::Vector2() : X(0.0f), Y(0.0f)
{
}

Vector2::Vector2(float _X, float _Y) : X(_X), Y(_Y)
{
}

Vector2::Vector2(const Vector2& Other) : X(Other.X), Y(Other.Y)
{
}

float Vector2::Length()
{
	return std::sqrt(X*X + Y*Y);
}

float Vector2::LengthSquared()
{
	return X*X + Y*Y;
}

void Vector2::Normalize()
{
	float _Length = Length();
	X /= _Length;
	Y /= _Length;
}

Vector2& Vector2::operator=(const Vector2& Other)
{
	if (this != &Other)
	{
		this->X = Other.X;
		this->Y = Other.Y;
	}
	return *this;
}

Vector2& Vector2::operator+=(const Vector2 & Other)
{
	X += Other.X;
	Y += Other.Y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 & Other)
{
	X -= Other.X;
	Y -= Other.Y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2 & Other)
{
	X *= Other.X;
	Y *= Other.Y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2 & Other)
{
	X /= Other.X;
	Y /= Other.Y;
	return *this;
}

Vector2 & Vector2::operator+=(const float Scalar)
{
	X += Scalar;
	Y += Scalar;
	return *this;
}

Vector2 & Vector2::operator-=(const float Scalar)
{
	X -= Scalar;
	Y -= Scalar;
	return *this;
}

Vector2 & Vector2::operator*=(const float Scalar)
{
	X *= Scalar;
	Y *= Scalar;
	return *this;
}

Vector2 & Vector2::operator/=(const float Scalar)
{
	X /= Scalar;
	Y /= Scalar;
	return *this;
}

bool Vector2::operator==(const Vector2& Other)
{
	return X == Other.X && Y == Other.Y;
}

bool Vector2::operator!=(const Vector2& Other)
{
	return !(*this == Other);
}



Vector2::~Vector2()
{
}