#pragma once

#include <cstddef>

namespace MyLibrary
{

	template <class T>
	class Iterator
	{

	public:
		Iterator(T* p) : ptr(p) {}

		bool operator== (const Iterator& other);
		bool operator!= (const Iterator& other);

		//when dereferencing the iterator we want to return the dereferenced pointer
		T& operator*() const;

		//for iterator + int
		Iterator<T> operator+(std::ptrdiff_t n) const;

		//pre-increment/decrement
		Iterator<T>& operator++();
		Iterator<T>& operator--();

		//post-increment
		Iterator<T>& operator++(int);
		Iterator<T>& operator--(int);

	private:
		//pointer to the current data
		T* ptr;

	};

	template<class T>
	bool Iterator<T>::operator==(const Iterator& other)
	{
		return (this->ptr == other.ptr);
	}

	template<class T>
	bool Iterator<T>::operator!=(const Iterator& other)
	{
		return (this->ptr != other.ptr);
	}

	template<class T>
	T& Iterator<T>::operator*() const
	{
		return *ptr;
	}

	template<class T>
	Iterator<T> Iterator<T>::operator+(std::ptrdiff_t n) const
	{
		return Iterator<T>(ptr + n);
	}

	template<class T>
	Iterator<T>& Iterator<T>::operator++()
	{
		++ptr;
		return *this;
	}

	template<class T>
	Iterator<T>& Iterator<T>::operator--()
	{
		--ptr;
		return *this;
	}

	template<class T>
	Iterator<T>& Iterator<T>::operator++(int)
	{
		//store current this
		Iterator tmp = *this;

		//increment - this calls the operator++() implementation above
		++(*this);

		//return temp value
		return tmp;
	}

	template<class T>
	Iterator<T>& Iterator<T>::operator--(int)
	{
		//store current this
		Iterator tmp = *this;

		//increment - this calls the operator++() implementation above
		--(*this);

		//return temp value
		return tmp;
	}

}