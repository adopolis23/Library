#include "Vector.h"

int main(int argc, char** argv)
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

	std::cout << vector->ToString();
}