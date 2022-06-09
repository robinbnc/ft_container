#include <vector>
#include <iostream>
#include <exception>
#include <memory>
#include "Vector.hpp"

int 	main()
{
	std::cout << "\t___THE VECTOR___" << std::endl;
	{
		std::vector<int> test(0, 6);
		std::cout << test.size() << std::endl;
		std::cout << test.max_size() << std::endl;
		std::cout << test.capacity() << std::endl;
		std::cout << test.empty() << std::endl;
	}
	std::cout << std::endl;
	std::cout << "\t___MY VECTOR___" << std::endl;
	{
		ft::vector<int> test(0, 6);
		std::cout << test.size() << std::endl;
		std::cout << test.max_size() << std::endl;
		std::cout << test.capacity() << std::endl;
		std::cout << test.empty() << std::endl;
	}
	return (0);
}