#include <iostream>
#include "Vector.h"

int main() {
	

	brandon::Vector<int> vec;

	vec.push_back(2);
	vec.push_back(10);
	vec.push_back(15);
	vec.push_back(2);

	
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		std::cout << *iter << std::endl;
	}


	return 0;
}