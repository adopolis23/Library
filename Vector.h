#pragma once

#include <math.h>


namespace brandon {

	//TODO: look up constexpr
	static constexpr std::size_t growth_factor = 2; 


	template<typename T>
	class Vector {

	public:

		using pointer = T*;
		using size_type = std::size_t;
		using alloc_traits = std::allocator_traits<std::allocator<T>>;


		//constructors
		Vector() { 
		grow_(); 
		grow_();
		grow_();
		}



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
				throw std::length_error("brandon::vector unable to grow");
			}

			size_type newSize = static_cast<size_type>(Capacity() * growth_factor + 1);
			//newSize = std::min((int)newSize, std::abs((int)max_size()));

			if (newSize > max_size() || newSize <= 0) {
				throw std::length_error("brandon::vector invalid new length");
			}

			change_capacity_(newSize);
		}









		void change_capacity_(size_type new_size) {
			pointer new_buf = alloc_traits::allocate(m_allocator, new_size);

			//if buffer already exists w/ items we need to copy to new bufer
 			if (m_buffer) {

				//if the type of the vector is trvially copyable just do an unit copy to new memory
				if constexpr (std::is_trivially_copyable_v<T>) {
					std::uninitialized_copy(m_buffer, m_buffer + Size(), new_buf);
				}
				else {
					//if it needs a deep copy use construct and as arguemtn pass move if no excpet
					//this may throw an error
					for (size_type i = 0; i < Size(); ++i) {
						alloc_traits::construct(m_allocator, &new_buf[i],
							std::move_if_noexcept(m_buffer[i]));
					}
				}

				destroy_all_();

				//deallocate m_buffer
				alloc_traits::deallocate(m_allocator, m_buffer, Capacity());
			}

			//set member buff to be the new buffer just created and set capacity
			m_buffer = new_buf;
			m_capacity = new_size;
		}


		void destroy_all_() {
			if constexpr (!std::is_trivially_destructible_v<T>) {
				for (size_type i = 0; i < Size(); i++) {
					destroy_one_(&m_buffer[i]);
				}
			}
		}


		void destroy_one_(pointer ptr) {
			if constexpr (!std::is_trivially_destructible_v<T>) {
				alloc_traits::destroy(m_allocator, ptr);
			}
		}




	private:
		std::allocator<T> m_allocator;
		pointer m_buffer = nullptr;
		size_type m_size = 0;
		size_type m_capacity = 0;


	};

};