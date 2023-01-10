#include <iostream>
#include "Vector.h"

int main() {
	

	brandon::Vector<int> vec;

	vec.push_back(2);
	vec.push_back(10);
	vec.push_back(15);
	vec.push_back(2);

	std::cout << vec[2];


	return 0;
}