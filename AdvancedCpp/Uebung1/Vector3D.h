#pragma once

class Vector3D{
private:
    double x, y, z;

public:

    Vector3D() {
        x = 0;
        y = 0;
        z = 0;
    };
    Vector3D(double x, double y, double z);

    double getX();
    double getY();
    double getZ();
    void setX(const double x);
    void setY(const double y);
    void setZ(const double z);
    double length();
    double dot(Vector3D other);
    Vector3D cross(Vector3D other);

    Vector3D operator+(Vector3D other);
    Vector3D operator-(Vector3D other);
    Vector3D operator*(Vector3D other);
    void operator+=(Vector3D other);
    void operator-=(Vector3D other);
    void operator*=(Vector3D other);
    Vector3D operator+(double scalar);
    Vector3D operator-(double scalar);
    Vector3D operator*(double scalar);
    void operator+=(double scalar);
    void operator-=(double scalar);
    void operator*=(double scalar);
};
