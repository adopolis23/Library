#pragma once



namespace brandon {

	//TODO: look up constexpr
	static constexpr std::size_t growth_factor = 1.5; 


	template<typename T>
	class Vector {

	public:

		using pointer = T*;
		using size_type = std::size_t;
		using alloc_traits = std::allocator_traits<std::allocator<T>>;


		//constructors
		Vector() {}



		//public functions
		size_type Size() const { return m_size; }
		size_type Capacity() const { return m_capacity;  }
		size_type max_size() const { return alloc_traits::max_size(m_allocator); }
		//size_type max_size() const { return std::allocator_traits <std::allocator<T>>::max_size(m_allocator); }


	private:

		//private functions
		void grow_()
		{
			if (Size() >= max_size()) {
				std::cout << "Error: brandon::vector Cannot Grow" << std::endl;
			}

			size_type newSize = std::max(1, (int)(Capacity() * growth_factor));
			newSize = std::min((int)newSize, (int)max_size());

			auto new_buf = alloc_traits::allocate(m_allocator, newSize);
		}


	private:
		std::allocator<T> m_allocator;
		pointer m_buffer = nullptr;
		size_type m_size = 0;
		size_type m_capacity = 0;


	};

};