#pragma once

#include "Core.h"
#include "Allocator.h"
#include "Iterator.h"

#include <iostream>
#include <malloc.h>
#include <new>
#include <sstream>

namespace MyLibrary
{

	//custom vector class
	template <class T, class Allocator = MyLibrary::Allocator<T>>
	class Vector
	{
		//usings to make types easier
		using size_type = size_t;
		using value_type = T;
		using ref_type = value_type&;
		using const_ref_type = const ref_type;
		using pointer_type = T*;

		//might need pointer* and iterator and allocator ???
	public:
		//constructors
		Vector(); //no args
		Vector(int capacity); //size of initial allocation
		//Vector(const Vector<T, Allocator>& other);
		~Vector();

		//member functions
		value_type At(unsigned int index) const;
		void PushBack(value_type item);
		std::string ToString() const;
		int GetSize() const;

		//iterator member functions
		Iterator<T> Begin();
		Iterator<T> End();

		//operators
		Vector<T, Allocator>& operator= (const Vector<T>& other); //equivelant to this.operator=(other)
		ref_type operator[] (int i);
		const T& operator[] (int i) const;

	private:
		//constructs elements, important for complex types
		void _ConstructElements();
		
		//increases the size of the data array, doubles???
		void _Grow();

		//hold data for all items in the vector. Will be resized dyanmically
		pointer_type _data = nullptr;
		size_type _size = 0;
		size_type _capacity = 0;
		size_type _growthFactor = 2;

		Allocator Allocator;
	};

	//constructor
	template <typename T, class Allocator>
	Vector<T, Allocator>::Vector(): _size(0), _capacity(2)
	{
		//initial allocaiton will be 2 items
		//_data = static_cast<pointer_type>(malloc(sizeof(value_type) * 2));
		_data = Allocator.Allocate(2);

		if (!_data)
		{
			throw std::bad_alloc();
		}
		_ConstructElements();
	}


	//constructor size arg
	template <typename T, class Allocator>
	Vector<T, Allocator>::Vector(int capacity) : _size(0), _capacity(capacity)
	{
		_data = Allocator.Allocate(capacity);

		if (!_data)
		{
			throw std::bad_alloc();
		}

		_ConstructElements();
	}

	//template<class T, class Allocator>
	//Vector<T, Allocator>::Vector(const Vector<T, Allocator>& other)
	//	: _size(other._size), _capacity(other._capacity)
	//{
	//	_data = Allocator.Allocate(_capacity);

	//	for (size_type i = 0; i < _size; i++)
	//	{
	//		//constructs T at each spot, calls T's copy constructor
	//		new(_data + i) T(other._data[i]);
	//	}
	//}

	//destructor
	template <typename T, class Allocator>
	Vector<T, Allocator>::~Vector()
	{
		Allocator.Deallocate(_data, _size);
	}


	//constructs elements in list
	template <typename T, class Allocator>
	void Vector<T, Allocator>::_ConstructElements()
	{
		Allocator.ConstructElements(_data, _size);
	}

	//returns element at index
	template <typename T, class Allocator>
	T Vector<T, Allocator>::At(unsigned int index) const
	{
		return _data[index];
	}

	template<typename T, class Allocator>
	void Vector<T, Allocator>::PushBack(value_type item)
	{
		if (_size == _capacity)
		{
			_Grow();
		}

		//_data[_size++] = item;
		//constructs the new item in place.
		new (_data + _size++) T(item);
	}

	//this is horrible and will need to be changed.
	template<typename T, class Allocator>
	std::string Vector<T, Allocator>::ToString() const
	{
		std::ostringstream oss;
		oss << "[";

		for (size_type i = 0; i < _size; ++i)
		{
			if (i > 0)
				oss << ", ";

			oss << _data[i];  // requires operator<< for T
		}

		oss << "]";
		return oss.str();
	}

	template<class T, class Allocator>
	int Vector<T, Allocator>::GetSize() const
	{
		return static_cast<int>(_size);
	}

	template<typename T, class Allocator>
	void Vector<T, Allocator>::_Grow()
	{
		//created new memory with size of current memory times growth factor
		pointer_type new_memory = Allocator.Allocate(_capacity * _growthFactor);

		//copy items from current memory into new memory
		for (size_type i = 0; i < _size; i++)
		{
			//construct new object at each location
			new(new_memory + i) T(_data[i]);

			//call destructor on each object
			_data[i].~T();
		}

		free(_data);

		_data = new_memory;
		
		_capacity = _capacity * _growthFactor;
		
	}

	template<class T, class Allocator>
	inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector<T>& other)
	{
		if (this != &other)
		{
			size_type new_size = other._size;

			//deallocate current
			Allocator.Deallocate(_data, _size);

			//allocate and copy
			_data = Allocator.Allocate(other._capacity);

			this->_size = new_size;
			this->_capacity = other._capacity;

			for (size_type i = 0; i < _size; i++)
			{
				//construct new object at each position
				new(_data + i) T(other[i]);
			}
		}

		//this is to allow for chaining
		return *this;
	}

	template<class T, class Allocator>
	const T& Vector<T, Allocator>::operator[](int i) const
	{
		return _data[i];
	}

	template<class T, class Allocator>
	inline T& Vector<T, Allocator>::operator[](int i)
	{
		//TODO: Implement reverse indexing ie. vec[-1] should return last element
		return _data[i];
	}


	template<class T, class Allocator>
	Iterator<T> Vector<T, Allocator>::Begin()
	{
		return Iterator<T>(_data);
	}

	template<class T, class Allocator>
	Iterator<T> Vector<T, Allocator>::End()
	{
		return Iterator<T>(_data + _size - 1);
	}


};