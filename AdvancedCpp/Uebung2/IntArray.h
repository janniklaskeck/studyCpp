#pragma once

#include <iostream>

class IntArray
{
public:
	IntArray();
	IntArray(IntArray& other);
	IntArray(IntArray&& other);
	IntArray(int startingSize);
	~IntArray();

	void append(int element);
	void erase(int index);
	int getLength();

	int operator[](const int index);

private:

	int* m_ArrayStart;
	int m_CurrentLength = 0;

	void allocateMemory(int amount);
	void freeMemory();
	void resize(int newSize);
	
};

