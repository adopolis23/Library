#include "Core.h"

#include <iostream>

LIBRARY_API void Hello()
{
    std::cout << "Hello from DLL!" << std::endl;
}