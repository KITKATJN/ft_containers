#include "vector.hpp"
#include <iostream>
#include <iostream>
#include <string>
#include <type_traits>

template <typename T>
void print_vector(ft::vector<T> &v)
{
    for (size_t i = 0; i < v.size()+1; i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	ft::vector<std::string> v;
	v.push_back("ffff");
    print_vector(v);
    ft::vector<std::string> v5(2, "bonjour");
    print_vector(v5);
	// v[1] = 5;
	// std::cout << v[1] << std::endl;
	// std::cout << v.size() << std::endl;
	// std::cout << v.size() << std::endl;
	// for (size_t i = 0; i < v.size(); i++)
	// {
	// 	v[i] = i;
	// }
	// print_vector(v);
	// std::cout << std::endl;
	// v.erase(v.begin() + 2);
    // print_vector(v);
    // std::cout << v[9]  << " " << v[8] << std::endl;
    // v.resize(20);
    // print_vector(v);
    // v.resize(6);
	// v.pop_back();
    // print_vector(v);
	// v.insert(v.begin(), 90);
	// print_vector(v);
	// v.insert(v.begin() + 3, 4, 90);
	// print_vector(v);
	// v.pop_back();
    // print_vector(v);
    // v.push_back(67);
    // print_vector(v);
    // v.push_back(67);
    // print_vector(v);
    // std::cout << "cap = "<< v.capacity() << std::endl;
    // v.push_back(68);
    // print_vector(v);
    // std::cout << "cap = "<< v.capacity() << std::endl;
    // v.push_back(69);
    // print_vector(v);
    // v.push_back(70);
    // print_vector(v);
    // v.push_back(75);
    // print_vector(v);
	// v.reserve(20);
	// std::cout << "!!!!!!!!!!!!!" << v.capacity() << std::endl;
	// for (size_t i = 0; i < v.size(); i++)
	// {
	// 	std::cout << v[i] << " ";
	// }
	// std::cout << std::endl;
	// std::cout << "!!!!!" << std::endl;
	// v.erase(v.begin(), v.end() - 2);
	// for (size_t i = 0; i < v.size(); i++)
	// {
	// 	std::cout << v[i] << " ";
	// }
    // // std::cout << v[2] << " ";
	// std::cout << std::endl;
	// //v.clear();
	// std::cout << v.empty() << std::endl;
    // v.assign(5, 5);
    // print_vector(v);
    // ft::vector<int> extra(6, 9);
    // v.assign(extra.begin(), extra.end());
    // print_vector(v);
	return 0;
}
