#pragma once

namespace MyLibrary
{

	template <class T1, class T2>
	class Pair
	{

	public:

		//constructors
		Pair(T1& V1, T2& V2);

		//operators
		Pair<T1, T2>& operator= (const Pair<T1, T2>& other);

		//member functions
		void Swap(Pair<T1, T2>& other);

	private:
		T1 _V1;
		T2 _V2;

	};

	template<class T1, class T2>
	Pair<T1, T2>::Pair(T1& V1, T2& V2)
		: _V1(V1), _V2(V2)
	{

	}

	template<class T1, class T2>
	Pair<T1, T2>& Pair<T1, T2>::operator=(const Pair<T1, T2>& other)
	{
		if (this != &other)
		{
			_V1 = other._V1;
			_V2 = other._V2;
		}

		return *this;
	}

	template<class T1, class T2>
	void Pair<T1, T2>::Swap(Pair<T1, T2>& other)
	{
		T1 tmp_V1 = this->_V1;
		this->_V1 = other._V1;
		other._V1 = tmp_V1;

		T2 tmp_V2 = this->_V2;
		this->_V2 = other._V2;
		other._V2 = tmp_V2;
	}

}