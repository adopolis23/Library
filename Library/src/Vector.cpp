#include "Vector.h"

#include <iostream>

namespace MyLibrary
{
	//constructor
	template <typename T>
	Vector<T>::Vector(): _size(2), _capacity(2)
	{
		//initial allocaiton will be 2 items
		_data = static_cast<pointer_type>(std::malloc(sizeof(value_type) * 2));

		if (!_data)
		{
			throw std::bad_alloc();
		}

		_ConstructElements();
	}

	//constructor size arg
	template <typename T>
	Vector<T>::Vector(int size): _size(size), _capacity(size)
	{
		//initial allocaiton will be 2 items
		_data = static_cast<pointer_type>(std::malloc(sizeof(value_type) * size));

		if (!_data)
		{
			throw std::bad_alloc();
		}

		_ConstructElements();
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


}