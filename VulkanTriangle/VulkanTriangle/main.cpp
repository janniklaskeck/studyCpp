#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>

#include "Triangle.h"

int main()
{
	Triangle triangle;

	try
	{
		triangle.Run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}