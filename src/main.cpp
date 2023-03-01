#include <iostream>
#include <ft/vector.hpp>
int	main(void)
{
	std::cout << "Hello World !" << std::endl;
	ft::vector<int> NewVector;
	NewVector.push_back(42);
	std::cout << "Play 42 please :" << NewVector[0] << std::endl;
	return (0);
}

