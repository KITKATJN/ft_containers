#include <vector>
#include <iostream>

int main()
{
    std::vector<int> array { 12, 10, 8, 6, 4, 2, 1 };
    std::cout << "The length is: " << array.size() << '\n';

	array.begin();
	array.data();
	array.at();
	array.empty();
	array.size();
	array.max_size();
	~array();
    return 0;
}
