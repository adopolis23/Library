#pragma once

#include <Malloc.h>

namespace MyLibrary
{
	//allocator class to handle memory allocating and freeing

	template <class T>
	class Allocator
	{
		using value_type = T;
		using pointer_type = T*;
		using size_type = size_t;

	public:
		pointer_type Allocate(size_t n);
		void Deallocate(pointer_type p, size_t n);
		void ConstructElements(pointer_type p, size_t n);

	private:
	};


	//allocates N bytes and returns a T* pointer to their base address
	template<class T>
	inline T* Allocator<T>::Allocate(size_t n)
	{
		return static_cast<pointer_type>(malloc(sizeof(value_type) * n));
	}

	template<class T>
	inline void Allocator<T>::Deallocate(pointer_type p, size_t n)
	{
		for (size_type i = 0; i < n; i++)
		{
			//call destructor on each object
			(p + i)->~T();
		}

		free(p);
	}

	template<class T>
	inline void Allocator<T>::ConstructElements(pointer_type p, size_t n)
	{
		// Construct each element using placement new
		for (size_type i = 0; i < n; ++i) {
			new(p + i) T(); // calls T's default constructor in-place
		}
	}



};