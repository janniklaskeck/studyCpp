#include <cmath>
#include "Vector3D.h"


Vector3D::Vector3D(){
    x = 0;
    y = 0;
    z = 0;
}

Vector3D::Vector3D(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

const Vector3D Vector3D::operator+(const float rhs) const
{
	return Vector3D(this->x + rhs, this->y + rhs, this->z + rhs);
}

const Vector3D Vector3D::operator-(const float rhs) const
{
	return Vector3D(this->x - rhs, this->y - rhs, this->z - rhs);
}

const Vector3D Vector3D::operator+(const Vector3D rhs) const
{
	return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
}

const Vector3D Vector3D::operator-(const Vector3D rhs) const
{
	return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
}


// * operator for multiplying with a scalar (vector * scalar)
const Vector3D Vector3D::operator * (const float rhs) const
{
    return Vector3D(this->x * rhs, this->y * rhs, this->z * rhs);
}

// * operator for multiplying with a scalar (scalar * vector)
Vector3D operator * (const float rhs, const Vector3D& v)
{
	return Vector3D(v.x * rhs, v.y * rhs, v.z * rhs);
}

// / operator for dividing by a scalar
const Vector3D Vector3D::operator / (const float rhs) const
{
    return Vector3D(this->x / rhs, this->y / rhs, this->z / rhs);
}

// += operator
Vector3D& Vector3D::operator += (const Vector3D& rhs) 
{
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}

// -= operator
Vector3D& Vector3D::operator -= (const Vector3D& rhs)
{
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}

// *= operator (scalar)
Vector3D& Vector3D::operator *= (const float rhs)
{
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}

// /= operator (scalar)
Vector3D& Vector3D::operator /= (const float rhs)
{
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}

// unary - operator
const Vector3D Vector3D::operator - () const
{
    return Vector3D(-x,-y,-z);
}


// returns the length of the vector
float Vector3D::length() const
{
    return sqrt(x*x + y*y + z*z);
}

// computes the dot product of this and another 3 component vector
float Vector3D::dot(const Vector3D& rhs) const
{
    return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z;
} 

// computes the cross product of this and another 3 component vector
const Vector3D Vector3D::cross(const Vector3D& rhs) const
{
    Vector3D res;
    res.x = this->y * rhs.z - this->z * rhs.y;
    res.y = this->z * rhs.x - this->x * rhs.z;
    res.z = this->x * rhs.y - this->y * rhs.x;
    return res;
}

// returns a normalized version of this vector
const Vector3D Vector3D::normalized() const
{
    return (*this) / this->length();
}
