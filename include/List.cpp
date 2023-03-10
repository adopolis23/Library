

namespace brandon {

	template<typename Type>
	class List {


		struct Node_Base {
			Node_Base* m_Next, m_Prev;
		};

		template<typename Type>
		struct Node : Node_Base {

			Type data;
		};



		using size_type = std::size_t;
		using pointer = Type*;
		using reference = Type&;

		using alloc_traits = std::allocator_traits<std::allocator<Type>>;

		class iterator {
		public:
			Node_Base* m_ptr;

			iterator(Node_Base* node) : m_ptr{ node } {}
		};


	public:



	private:

		void link_nodes_(Node_base* first, Node_Base* last) {
			first->m_Next = last;
			last->m_Prev = first;
		}


	private:
		//type allocator
		std::allocator<T> m_allocator;

		//Node allocator
		std::allocator<Node> m_NodeAllocator;

		pointer m_buffer = nullptr;



	};


}