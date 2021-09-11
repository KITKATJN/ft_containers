#include <vector>
#include <iostream>

int main()
{
    // std::vector<int> array { 12, 10, 8, 6, 4, 2, 1 };
    // std::cout << "The length is: " << array.size() << '\n';

	// array.begin();
	// array.data();
	// array.at();
	// array.empty();
	// array.pop_back
	// array.size();
	// array.max_size();
	// ~array();
		std::vector<int> v(10, 10);
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
    return 0;
}
