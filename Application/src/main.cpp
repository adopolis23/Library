#include "Vector.h"

void function();

int main(int argc, char** argv)
{
	function();

	return 0;
}

void function()
{
	//test of initialization
	MyLibrary::Vector<int>* vector = new MyLibrary::Vector<int>();
	
	//tst of auto grow
	vector->PushBack(1);
	vector->PushBack(2);
	vector->PushBack(3);
	vector->PushBack(4);

	//test of to string
	std::cout << vector->ToString() << std::endl;
	
	//test of at
	std::cout << vector->At(2) << std::endl;

	//test of operator=
	MyLibrary::Vector<int> vector2 = *vector;

	vector2[1] = 60;
	std::cout << vector2.ToString() << std::endl;

	//test of operator[]
	//int x = vector2[0];
}