#include "set.hpp"
#include <map>

int main()
{
    ft::set<int> ft_map ;// (ft::pair<int,int>(1,1));

	for (int i = 0; i < 100; i++) {
		ft_map.insert(i);
	}
	ft_map.find(12343);
	std::cout << (ft_map.find(-3) == ft_map.end()) << std::endl;
	// for (int i = 100; i > 0; i--) {
	// 	ft_map.erase(i);
	// }
}
