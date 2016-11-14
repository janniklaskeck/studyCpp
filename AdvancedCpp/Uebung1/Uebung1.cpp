// Uebung1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Vector3D.h"
#include "Board.h"

using namespace std;

int main()
{
    // constructor
    Vector3D first;
    cout << first.getX() << endl;
    // constructor parameter
    Vector3D second(11,22,33);
    cout << second.getX() << endl;
    // length
    cout << second.length() << endl;
    // add and subtract vectors
    Vector3D a(3,2,1);
    Vector3D b(1,2,3);
    cout << (a - b).getX() << endl;
    // add and subtract scalar
    const int scalar = 2;
    cout << (a + scalar).getX() << endl;
    // multiplication scalar
    cout << (a * 2).getX() << endl;
    // multiplication vector
    cout << (a * b).getY() << endl;
    // assignment operators
    a += Vector3D(1, 1, 1);
    cout << a.getX() << endl;
    b -= Vector3D(1, 1, 1);
    cout << b.getX() << endl;
    a *= Vector3D(2, 2, 2);
    cout << a.getX() << endl;
    // dot
    cout << a.dot(b) << endl;
    // cross
    cout << a.cross(b).getX() << endl;

    Board board;
    board.render();
    return 0;
}
