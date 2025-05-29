#pragma once


namespace MyLibrary
{
	//Custom hash functionality
	template<typename T>
	struct Hash;

	//integer has, TODO: implement a real hash algorithm
	template<>
	struct Hash<int> {
		size_t operator()(int input) const {
			return static_cast<size_t>(input);
		}
	};


}
