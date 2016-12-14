#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D(double x, double y, double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

double Vector3D::getX() {
	return x;
}

double Vector3D::getY() {
	return y;
}

double Vector3D::getZ() {
	return z;
}

void Vector3D::setX(const double x) {
	this->x = x;
}

void Vector3D::setY(const double y) {
	this->y = y;
}

void Vector3D::setZ(const double z) {
	this->z = z;
}

double Vector3D::length() {
	const double length = sqrt(x * x + y * y + z * z);
	return length;
}

Vector3D Vector3D::operator+(Vector3D other) {
	Vector3D newVector;
	newVector.setX(this->x + other.getX());
	newVector.setY(this->y + other.getY());
	newVector.setZ(this->z + other.getZ());
	return newVector;
}

Vector3D Vector3D::operator-(Vector3D other) {
	Vector3D newVector;
	newVector.setX(this->x - other.getX());
	newVector.setY(this->y - other.getY());
	newVector.setZ(this->z - other.getZ());
	return newVector;
}

Vector3D Vector3D::operator*(Vector3D other) {
	Vector3D newVector;
	newVector.setX(this->x * other.getX());
	newVector.setY(this->y * other.getY());
	newVector.setZ(this->z * other.getZ());
	return newVector;
}

void Vector3D::operator+=(Vector3D other) {
	this->x += other.getX();
	this->y += other.getY();
	this->z += other.getZ();
}

void Vector3D::operator-=(Vector3D other) {
	this->x -= other.getX();
	this->y -= other.getY();
	this->z -= other.getZ();
}

void Vector3D::operator*=(Vector3D other) {
	this->x *= other.getX();
	this->y *= other.getY();
	this->z *= other.getZ();
}

Vector3D Vector3D::operator*(double other) {
	Vector3D newVector;
	newVector.setX(this->x * other);
	newVector.setY(this->y * other);
	newVector.setZ(this->z * other);
	return newVector;
}

Vector3D Vector3D::operator+(double other) {
	if (other == 0.0) {
		return *this;
	}
	Vector3D newVector;
	newVector.setX(this->x + other);
	newVector.setY(this->y + other);
	newVector.setZ(this->z + other);
	return newVector;
}

Vector3D Vector3D::operator-(double other) {
	if (other == 0.0) {
		return *this;
	}
	Vector3D newVector;
	newVector.setX(this->x - other);
	newVector.setY(this->y - other);
	newVector.setZ(this->z - other);
	return newVector;
}

void Vector3D::operator+=(double other) {
	this->x += other;
	this->y += other;
	this->z += other;
}

void Vector3D::operator-=(double other) {
	this->x -= other;
	this->y -= other;
	this->z -= other;
}

void Vector3D::operator*=(double other) {
	this->x *= other;
	this->y *= other;
	this->z *= other;
}

Vector3D Vector3D::cross(Vector3D other) {
	Vector3D cross;
	cross.setX(this->y * other.getZ() - this->z * other.getY());
	cross.setY(this->z * other.getX() - this->x * other.getZ());
	cross.setZ(this->x * other.getY() - this->y * other.getX());
	return cross;
}

double Vector3D::dot(Vector3D other) {
	double sum = 0.0;
	sum += this->x * other.getX();
	sum += this->y * other.getY();
	sum += this->z * other.getZ();
	return sum;
}
