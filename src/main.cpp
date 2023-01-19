#include <iostream>
#include "Vector.h"

int main() {
	

	brandon::Vector<int> vec;


	
	vec.push_back(2);
	vec.push_back(10);
	vec.push_back(15);
	vec.push_back(2);
	vec.push_back(1);

	brandon::Vector<int> vec2(vec);


	for (auto iter = vec2.begin(); iter != vec2.end(); iter++) {
		std::cout << *iter << std::endl;
	}


	return 0;
}