module;

#include <iostream>

export module Minairo;

export void API MyFunc();

export void API MyFunc2()
{
	std::cout << "hello world 2" << std::endl;
}

