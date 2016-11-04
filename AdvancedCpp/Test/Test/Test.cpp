// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#define pr(s) std::cout << s << std::endl;

using namespace std;

void print(float in)
{
	cout << in << endl;
}
int main()
{
	double ba = 0.0;
	int asd = 123;
	print(asd);
	int a = 1;
	pr(a);
	int* p = nullptr;
	pr(p);
	p = &a;
	pr(p);
	p++;
	pr(p);
	int b = *p;
	pr(b);


	int tmp;
	cin >> tmp;
	return 0;
}

