#pragma once

namespace MyLibrary
{


	template <class KeyType, class ValueType>
	class Hashtable
	{

	public:
		//constructors
		Hashtable();

	private:
		int _NumBuckets = 8;

		//in this implementation I will use seperate chaining
		MyLibrary::Vector<MyLibrary::Vector<MyLibrary::Pair<KeyType, ValueType>>> _Buckets;

	};



}