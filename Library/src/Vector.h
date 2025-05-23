#include "Core.h"

namespace MyLibrary
{

	//custom vector class
	template <class T>
	class LIBRARY_API Vector
	{
		//usings to make types easier
		using size_type = std::size_t;
		using value_type = T;
		using ref_type = value_type&;
		using const_ref_type = const ref_type;
		using pointer_type = T*;

		//might need pointer* and iterator and allocator ???
	public:
		//constructors
		Vector(); //no args
		Vector(int size); //size of initial allocation
		~Vector();

	private:
		//constructs elements, important for complex types
		void _ConstructElements();

		//hold data for all items in the vector. Will be resized dyanmically
		pointer_type _data = nullptr;
		size_type _size = 0;
		size_type _capacity = 0;

	};

};