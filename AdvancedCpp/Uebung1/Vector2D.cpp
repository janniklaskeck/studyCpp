#include "stdafx.h"
#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D(int x, int y) {
    this->x = x;
    this->y = y;
}

int Vector2D::getX() {
    return x;
}

int Vector2D::getY() {
    return y;
}

void Vector2D::setX(const int x) {
    this->x = x;
}

void Vector2D::setY(const int y) {
    this->y = y;
}

double Vector2D::length() {
    return sqrt(x * x + y * y);
}

int Vector2D::dot(Vector2D other) {
    return this->x * other.getX() + this->y * other.getY();
}

Vector2D Vector2D::cross(Vector2D other) {
    return Vector2D();
}

Vector2D Vector2D::operator+(Vector2D other) {
    Vector2D newVector;
    newVector.setX(this->x + other.getX());
    newVector.setY(this->y + other.getY());
    return newVector;
}

Vector2D Vector2D::operator+(int scalar) {
    Vector2D newVector;
    newVector.setX(this->x + scalar);
    newVector.setY(this->y + scalar);
    return newVector;
}

Vector2D Vector2D::operator-(Vector2D other) {
    Vector2D newVector;
    newVector.setX(this->x - other.getX());
    newVector.setY(this->y - other.getY());
    return newVector;
}

Vector2D Vector2D::operator-(int scalar) {
    Vector2D newVector;
    newVector.setX(this->x - scalar);
    newVector.setY(this->y - scalar);
    return newVector;
}

Vector2D Vector2D::operator*(Vector2D other) {
    Vector2D newVector;
    newVector.setX(this->x * other.getX());
    newVector.setY(this->y * other.getY());
    return newVector;
}

Vector2D Vector2D::operator*(int scalar) {
    Vector2D newVector;
    newVector.setX(this->x * scalar);
    newVector.setY(this->y * scalar);
    return newVector;
}

void Vector2D::operator*=(Vector2D other) {

}

void Vector2D::operator-=(Vector2D other) {

}

void Vector2D::operator+=(Vector2D other) {
    this->x += other.getX();
    this->y += other.getY();
}

void Vector2D::operator*=(int scalar) {

}

void Vector2D::operator-=(int scalar) {

}

void Vector2D::operator+=(int scalar) {

}

