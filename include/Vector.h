#pragma once

#include <math.h>
#include <assert.h>

namespace brandon {

	//TODO: look up constexpr
	static constexpr std::size_t growth_factor = 2; 


	template<typename T>
	class Vector {

	public:

		using pointer = T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = std::size_t;
		using alloc_traits = std::allocator_traits<std::allocator<T>>;
		using difference_type = std::ptrdiff_t;



		class iterator {

		public:
			using size_type = std::size_t;
			using reference = T&;
			using pointer = T*;

			iterator(pointer ptr) {
				this->m_data = ptr;
			}

			//increment and decrement
			iterator& operator++() {
				++m_data;
				return *this; 
			}

			iterator operator++(int) {
				iterator ret = iterator{ *this };
				++m_data;
				return ret;
			}

			iterator& operator--() {
				--m_data;
				return *this;
			}


			//addition of values
			iterator& operator+=(difference_type n) {
				m_data += n;
				return *this;
			}

			iterator& operator-=(difference_type n) {
				m_data -= n;
				return *this;
			}

			reference operator*() {
				return *m_data; 
			}


			friend bool operator==(const iterator& left, const iterator& right) {
				return (left.m_data == right.m_data);
			}

			friend bool operator!=(const iterator& left, const iterator& right) {
				return !(left == right);
			}


			friend bool operator<(const iterator& left, const iterator& right) {
				return left.m_data < right.m_data; 
			}

			friend bool operator>(const iterator& left, const iterator& right) {
				return right < left; 
			}

			friend bool operator<=(const iterator& left, const iterator& right) {
				return (left < right || left == right);
			}

			friend bool operator>=(const iterator& left, const iterator& right) {
				return (left > right || left == right);
			}



		private:
			pointer m_data;

		};



		//constructors
		Vector() { }

		
		//creates a vector with a count and value
		Vector(size_type count, const T& value) {
			change_capacity_(count);

			for (size_type i = 0; i < count; i++) {
				//m_buffer[i] = value;
				push_back(value);
			}
		}

		//creats a vector from an iterator of another vector
		Vector(iterator first, iterator last) {
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		Vector(const Vector& other) {
			m_buffer = alloc_traits::allocate(m_allocator, other.Size());

			if (other.Size() > 0) {
			

				//if the type of the vector is trvially copyable just do an unit copy to new memory
				if constexpr (std::is_trivially_copyable_v<T>) {
					
					for (int i = 0; i < other.Size(); i++) {
						push_back(other[i]);
					}

				}
				else {
					
					//No idea for this one

				}


			}

			m_size = other.Size();
			m_capacity = other.Capacity();
		}



		//public functions
		size_type Size() const { return m_size; }
		size_type Capacity() const { return m_capacity;  }
		size_type max_size() const { return alloc_traits::max_size(m_allocator); }
		//size_type max_size() const { return std::allocator_traits <std::allocator<T>>::max_size(m_allocator); }


		//adding item

	
		void push_back(const T& value) {
			//if no room for element then grow; then construct item at back of buffer; increase size

			if (Size() >= Capacity())
				grow_();

			//m_buffer[Size()] = value;
			alloc_traits::construct(m_allocator, &m_buffer[m_size], value);
			++m_size;
		}




		//removing elements
		T pop_back() {
			T tmp = m_buffer[m_size-1];
			destroy_one_(back());
			--m_size;
			return tmp;
		}



		//retrieving items

		reference at(size_type pos) {
			assert(pos < Size());
			return m_buffer[pos];
		}


		reference back() {
			return m_buffer[m_size-1];
		}

		reference front() {
			return m_buffer;
		}


		//operator overloads


		reference operator[](size_type pos) {
			assert(pos < Size());
			return m_buffer[pos];
		}

		reference operator[](size_type pos) const {
			assert(pos < Size());
			return m_buffer[pos];
		}


		//iterators
		iterator begin() { return iterator(m_buffer); }
		iterator end() { return iterator(&m_buffer[m_size]); }




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

		reference getData() {
			return m_buffer; 
		}



	private:
		std::allocator<T> m_allocator;
		pointer m_buffer = nullptr;
		size_type m_size = 0;
		size_type m_capacity = 0;


	};

};