#include "ft_containers/vector.hpp"
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
	ft::vector<int> v;

	for (size_t i = 0; i < 10; i++) {
		v.push_back(i);
	}

	ft::vector<int>::reverse_iterator it1 = v.rbegin();

	while (it1 != v.rend()) {
		std::cout << *it1 << '\n';
		it1++;
	}

	ft::vector<int>::iterator it2 = it1.base();
	while (it2 != v.end())
	{
		std::cout << *it2 << '\n';
		it2++;
	}
	
	
	

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
