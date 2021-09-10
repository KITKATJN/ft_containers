#include "vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> v(10, 10);
	std::cout << v[1] << std::endl;
	v[1] = 5;
	v.pop_back();
	std::cout << v[1] << std::endl;
	std::cout << v.size() << std::endl;
	v.erase(v.begin() + 2);
	std::cout << v.size() << std::endl;
	for (size_t i = 0; i < v.size(); i++)
	{
		v[i] = i;
	}
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;

	v.erase(v.end() - 5, v.end() - 3);
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
