#include "vector.hpp"
#include <iostream>

int main()
{
	ft::vector<int> v(10, 10);
	std::cout << v[1] << std::endl;
	v[1] = 5;
	std::cout << v[1] << std::endl;
	std::cout << v.size() << std::endl;
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
	v.erase(v.begin() + 2);
	v.pop_back();
	// v.reserve(20);
	// std::cout << "!!!!!!!!!!!!!" << v.capacity() << std::endl;
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "!!!!!" << std::endl;
	v.erase(v.begin(), v.end() - 2);
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
	v.clear();
	std::cout << v.empty() << std::endl;
	return 0;
}
