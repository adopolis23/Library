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
		std::string ToString() const;
		int GetSize() const;
		void Resize(size_type n, value_type val = value_type());
		size_type Capacity() const;
		bool Empty() const;
		void ShrinkToFit();

		//Modifiers
		void PushBack(value_type item);
		void PopBack();

		//need to redo this one
		void Insert(Iterator<T> position, size_type n, const T& val);

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

		//constructs the new item in place.
		new (_data + _size++) T(item);
	}

	template<class T, class Allocator>
	void Vector<T, Allocator>::PopBack()
	{
		//call destructor on last element
		_data[_size - 1].~T();

		_size = _size - 1;
	}

	template<class T, class Allocator>
	void Vector<T, Allocator>::Insert(Iterator<T> position, size_type n, const T& val)
	{
		while (_size + n > _capacity)
		{
			_Grow();
		}

		for (Iterator<T> i = this->End(); i != position; i--)
		{
			//concstruct new copy of T n places ahead of current position moving backward
			//might be unsane for some reason with the i+n part might need to come back to this
			new (&(*(i+n))) T(*i);

			//destror old object
			(*i).~T();
		}

		//this might have to be *position to get the T& that the iterator points too
		for (size_type i = 0; i < n; ++i) {
			new (&(*(position + i))) T(val);
		}

		_size = _size + n;
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

	template<class T, class Allocator>
	void Vector<T, Allocator>::Resize(size_type n, value_type val)
	{
		//content is reduced to its first n elements
		if (n < _size)
		{
			//destroy all elements greater than n
			for (size_type i = n; i < _size; i++)
			{
				(_data + i)->~T();
			}

			_size = n;
		}
		else if (n > _size)
		{
			while (n > _capacity)
			{
				_Grow();
			}

			//construct new element val on end of vector to n
			for (size_type i = _size; i < n; i++)
			{
				//_data[i] = val;
				new (_data + i) T(val);
			}

			_size = n;
		}

		//if n == _size do nothing
	}

	template<class T, class Allocator>
	size_t Vector<T, Allocator>::Capacity() const
	{
		return _capacity;
	}

	template<class T, class Allocator>
	bool Vector<T, Allocator>::Empty() const
	{
		return (_size == 0);
	}

	template<class T, class Allocator>
	void Vector<T, Allocator>::ShrinkToFit()
	{
		//allocate new memory that is the exact size for elements
		pointer_type new_memory = Allocator.Allocate(_size);

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

		_capacity = _size;
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
		int index;
		if (i < 0)
		{
			index = _size + i;
		}
		else
		{
			index = i;
		}

		return _data[index];
	}

	template<class T, class Allocator>
	inline T& Vector<T, Allocator>::operator[](int i)
	{
		int index;
		if (i < 0)
		{
			index = _size + i;
		}
		else
		{
			index = i;
		}

		return _data[index];
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