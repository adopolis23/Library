#include "Vector.h"

void function();

int main(int argc, char** argv)
{
	function();

	return 0;
}

void function()
{
	MyLibrary::Vector<int>* vector = new MyLibrary::Vector<int>();
	vector->PushBack(1);
	vector->PushBack(2);
	vector->PushBack(2);
	vector->PushBack(2);
	vector->PushBack(3);
	vector->PushBack(2);
	vector->PushBack(2);
	vector->PushBack(2);

	std::cout << vector->ToString() << std::endl;

	std::cout << vector->At(2);
}