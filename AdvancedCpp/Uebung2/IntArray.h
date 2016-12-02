#pragma once

#include <iostream>

#define PRINT(msg) std::cout << msg << std::endl;
#define PRINTARRAY(array, length) \
for(int i = 0; i < length; i++) \
    PRINT(array[i]);
class IntArray
{
public:
	IntArray();
	IntArray(const IntArray& other);
	IntArray(IntArray&& other);
	IntArray(int startingSize);
	~IntArray();

	void append(int element);
	void erase(int index);
	int getLength() const;

	int& operator[](const int index) const;
	IntArray& operator=(const IntArray& other);

private:

	int* m_Array;
	int m_CurrentLength = 0;
	int m_ReservedCapacity = 0;

	void resize(const int newSize);
	
};

