#include <vector>
#include <iostream>

// int main()
// {
//     // std::vector<int> array { 12, 10, 8, 6, 4, 2, 1 };
//     // std::cout << "The length is: " << array.size() << '\n';

// 	// array.begin();
// 	// array.data();
// 	// array.at();
// 	// array.empty();
// 	// array.pop_back
// 	// array.size();
// 	// array.max_size();
// 	// ~array();
// 		std::vector<int> v(10, 10);
// 	std::cout << v[1] << std::endl;
// 	v[1] = 5;
// 	std::cout << v[1] << std::endl;
// 	std::cout << v.size() << std::endl;
// 	std::cout << v.size() << std::endl;
// 	for (size_t i = 0; i < v.size(); i++)
// 	{
// 		v[i] = i;
// 	}
// 	for (size_t i = 0; i < v.size(); i++)
// 	{
// 		std::cout << v[i] << " ";
// 	}
// 	std::cout << std::endl;
// 	v.erase(v.begin() + 2);
// 	for (size_t i = 0; i < v.size(); i++)
// 	{
// 		std::cout << v[i] << " ";
// 	}
// 	std::cout << std::endl;
// 	std::cout << "!!!!!" << std::endl;
// 	v.erase(v.begin(), v.end() - 2);
// 	for (size_t i = 0; i < v.size(); i++)
// 	{
// 		std::cout << v[i] << " ";
// 	}
// 	std::cout << std::endl;
//     return 0;
// }

void print_vector(std::vector<int> &v)
{
    for (size_t i = 0; i < v.size()+1; i++)
	{
		std::cout << v[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
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
	print_vector(v);
	std::cout << std::endl;
	v.erase(v.begin() + 2);
    print_vector(v);
    std::cout << v[9]  << " " << v[8] << std::endl;
    v.resize(20);
    print_vector(v);
    v.resize(6);
	v.pop_back();
    print_vector(v);
	v.insert(v.begin(), 90);
	print_vector(v);
	v.insert(v.begin() + 3, 4, 90);
	print_vector(v);
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
