#pragma once
#include <iostream>

template<typename T>
class UniquePtr
{
	T* m_ptr;

public:
	UniquePtr(const UniquePtr<T>& other) = delete;
	UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;

	UniquePtr() : m_ptr(nullptr) {};

	UniquePtr(UniquePtr<T>&& other)
	{
		m_ptr = other.m_ptr;
		other.m_ptr = nullptr;
	};
	UniquePtr<T>& operator=(UniquePtr<T>&& other)
	{
		if (this != &other)
		{
			delete m_ptr;
			m_ptr = other.m_ptr;
			other.m_ptr = nullptr;
		}
		return *this;
	};

	UniquePtr(T* ptr) : m_ptr(ptr) {};
	~UniquePtr()
	{
		std::cout << "delete player" << std::endl;
		delete m_ptr;
	};

	bool operator==(UniquePtr<T> other)
	{
		return other.get() == m_ptr;
	};

	T* operator->()
	{
		return m_ptr;
	};

	T& operator*() const
	{
		return *m_ptr;
	};

	T* get()
	{
		return m_ptr;
	};
};

