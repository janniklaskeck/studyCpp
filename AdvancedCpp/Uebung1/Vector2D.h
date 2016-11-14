#pragma once
class Vector2D {
private:
    int x, y;

public:

    Vector2D() {
        x = 0;
        y = 0;
    };
    Vector2D(int x, int y);

    int getX();
    int getY();
    void setX(const int x);
    void setY(const int y);
    int length();
    int dot(Vector2D other);
    Vector2D cross(Vector2D other);

    Vector2D operator+(Vector2D other);
    Vector2D operator-(Vector2D other);
    Vector2D operator*(Vector2D other);
    void operator+=(Vector2D other);
    void operator-=(Vector2D other);
    void operator*=(Vector2D other);
    Vector2D operator+(int scalar);
    Vector2D operator-(int scalar);
    Vector2D operator*(int scalar);
    void operator+=(int scalar);
    void operator-=(int scalar);
    void operator*=(int scalar);
};

