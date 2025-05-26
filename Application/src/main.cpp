#include "Vector.h"

void function();

int main(int argc, char** argv)
{
	function();

	return 0;
}

void function()
{
	MyLibrary::Vector<int> vec;
	vec.PushBack(1);
	vec.PushBack(2);
	vec.PushBack(3);



	std::cout << vec.ToString() << std::endl;

	vec.Insert(vec.Begin()+1, 1, 2);

	std::cout << vec.ToString() << std::endl;
}