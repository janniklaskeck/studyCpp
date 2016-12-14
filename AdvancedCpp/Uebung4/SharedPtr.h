#pragma once

template<typename T>
class SharedPtr
{
	T* m_ptr = nullptr;
	unsigned int* m_count = nullptr;

	void increment()
	{
		(*m_count)++;
	};

	void decrement()
	{
		(*m_count)--;
		if (m_count == 0)
		{
			delete m_ptr;
		}
	};
public:

	SharedPtr() : m_ptr(nullptr), m_count(nullptr) {};

	SharedPtr(T* ptr) : m_ptr(ptr), m_count(new unsigned int(1))
	{
	};

	~SharedPtr()
	{
		decrement();
	};

	SharedPtr(const SharedPtr<T>& other)
	{
		m_count = other.m_count;
		m_ptr = other.m_ptr;
		increment();
	};

	SharedPtr<T>& operator=(const SharedPtr<T>& other)
	{
		if (this != &other)
		{
			decrement();
			m_count = other.m_count;
			m_ptr = other.m_ptr;
			increment();
		}
		return *this;
	};

	SharedPtr(SharedPtr<T>&& other)
	{
		m_count = other.m_count;
		m_ptr = other.m_ptr;
		other.m_count = nullptr;
		other.m_ptr = nullptr;
	};

	SharedPtr<T>& operator=(SharedPtr<T>&& other)
	{
		if (this != &other)
		{
			delete m_ptr;
			delete m_count;
			m_count = other.m_count;
			m_ptr = other.m_ptr;
			other.m_count = nullptr;
			other.m_ptr = nullptr;
		}
		return this;
	};

	bool operator==(SharedPtr<T> other)
	{
		return other.get() == m_ptr;
	};

	T* operator->()
	{
		return m_ptr;
	};

	T& operator->() const
	{
		return *m_ptr;
	};

	T* get()
	{
		return m_ptr;
	};
};

