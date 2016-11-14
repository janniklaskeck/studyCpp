#include "IntArray.h"

IntArray::IntArray()
{

}

IntArray::IntArray(IntArray & other)
{

}

IntArray::IntArray(IntArray && other)
{

}

IntArray::IntArray(int startingSize)
{
	m_CurrentLength = startingSize;
}

IntArray::~IntArray()
{

}

void IntArray::append(int element)
{
	m_CurrentLength++;
}

void IntArray::erase(int index)
{

}

int IntArray::getLength()
{
	return m_CurrentLength;
}

int IntArray::operator[](const int index)
{
	return m_ArrayStart[index];
}

void IntArray::allocateMemory(int amount)
{

}

void IntArray::freeMemory()
{

}

void IntArray::resize(int newSize)
{

}
