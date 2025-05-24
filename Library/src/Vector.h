#pragma once

#include "Core.h"

#include <iostream>
#include <malloc.h>
#include <new>
#include <sstream>

namespace MyLibrary
{

	//custom vector class
	template <typename T>
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
		~Vector();

		//member functions
		value_type At(unsigned int index) const;
		void PushBack(value_type item);
		std::string ToString() const;

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
	};

	//constructor
	template <typename T>
	Vector<T>::Vector(): _size(0), _capacity(2)
	{
		//initial allocaiton will be 2 items
		_data = static_cast<pointer_type>(malloc(sizeof(value_type) * 2));

		if (!_data)
		{
			throw std::bad_alloc();
		}
		_ConstructElements();
	}


	//constructor size arg
	template <typename T>
	Vector<T>::Vector(int capacity) : _size(0), _capacity(capacity)
	{
		//initial allocaiton will be 2 items
		_data = static_cast<pointer_type>(malloc(sizeof(value_type) * capacity));

		if (!_data)
		{
			throw std::bad_alloc();
		}

		_ConstructElements();
	}

	//destructor
	template <typename T>
	Vector<T>::~Vector()
	{
		for (size_type i = 0; i < _size; i++)
		{
			//call destructor on each element
			_data[i].~T();
		}

		//free data array
		std::free(_data);
	}


	//constructs elements in list
	template <typename T>
	void Vector<T>::_ConstructElements()
	{
		// Construct each element using placement new
		for (size_type i = 0; i < _size; ++i) {
			new(&_data[i]) T(); // calls T's default constructor in-place
		}
	}

	//returns element at index
	template <typename T>
	T Vector<T>::At(unsigned int index) const
	{
		return _data[index];
	}

	template<typename T>
	void Vector<T>::PushBack(value_type item)
	{
		if (_size == _capacity)
		{
			_Grow();
		}

		_data[_size++] = item;
	}

	//this is horrible and will need to be changed.
	template<typename T>
	std::string Vector<T>::ToString() const
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

	template<typename T>
	void Vector<T>::_Grow()
	{
		//created new memory with size of current memory times growth factor
		pointer_type new_memory = static_cast<pointer_type>(malloc(sizeof(value_type) * _capacity * _growthFactor));

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

};