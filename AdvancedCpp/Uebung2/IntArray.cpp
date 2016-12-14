#include "IntArray.h"
#include <stdexcept>

IntArray::IntArray()
{
	m_Array = new int[0];
}

IntArray::IntArray(const IntArray& other)
{
	m_CurrentLength = other.getLength();
	//delete[] m_Array;
	m_Array = new int[other.getLength()];
	for (int i = 0; i < other.getLength(); i++)
	{
		int otherI = other[i];
		m_Array[0] = other[i];
	}
}

IntArray::IntArray(IntArray && other)
{
	m_Array = other.m_Array;
	other.m_Array = nullptr;
}

IntArray::IntArray(int startingSize)
{
	m_Array = new int[startingSize];
	m_ReservedCapacity = startingSize;
}

IntArray::~IntArray()
{
	delete[] m_Array;
}

void IntArray::append(int element)
{
	m_CurrentLength++;
	if (m_CurrentLength >= m_ReservedCapacity)
	{
		resize(m_CurrentLength);
	}
	m_Array[m_CurrentLength - 1] = element;
}

void IntArray::erase(int index)
{
	if (index >= m_CurrentLength || index < 0)
	{
		return;
	}
	m_CurrentLength--;
	IntArray tmp(*this);
	resize(m_ReservedCapacity);
	int tmpIndex = 0;
	int normalIndex = 0;
	while (normalIndex != m_CurrentLength - 1)
	{
		if (tmpIndex != index)
		{
			m_Array[normalIndex] = tmp[tmpIndex];
			normalIndex++;
		}
		tmpIndex++;
	}
}

int IntArray::getLength() const
{
	return m_CurrentLength;
}

int& IntArray::operator[](const int index) const
{
	if (index > getLength())
	{
		throw std::runtime_error("Wrong index!");
	}

	if (index < 0)
	{
		return m_Array[getLength() - index];
	}
	return m_Array[index];
}

IntArray& IntArray::operator=(const IntArray& other)
{
	if (&other == this)
	{
		return *this;
	}
	delete[] m_Array;
	m_Array = new int[other.getLength()];
	for (int i = 0; i < other.getLength(); i++)
	{
		m_Array[0] = other[i];
	}
	return *this;
}

void IntArray::resize(const int newSize)
{
	int* buffer = new int[newSize];
	m_ReservedCapacity = newSize;
	for (int i = 0; i < newSize; i++)
	{
		buffer[i] = m_Array[i];
	}
	delete[] m_Array;
	m_Array = buffer;
}
