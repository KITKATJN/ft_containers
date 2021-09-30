#include "rbtree.hpp"
#include "map.hpp"
#include <map>
#define RESET	"\033[0m"
#define GREEN	"\033[32m"
#define RED		"\033[31m"
#define MAGENTA "\033[35m"
#define LINE	"-----------------------------------------------"

int main() {
    // ft::rbtree<int, ft::less<int> > bst;
    // //bst.insert(ft::pair<int,int>(1, 5));
    // bst.insert(1);
    // bst.insert(5);
    // bst.insert(15);
    // bst.insert(17);
    // bst.insert(25);
    // //std::cout << "111111111111\n";
    // bst.erase(bst.begin());
    // //std::cout << "1111111111112\n";
    // bst.insert(40);
    // std::cout << bst.erase(40) << std::endl;
    // bst.insert(80);

    // //ft::map<std::string, int> m ;//{ {"CPU", 10}, {"GPU", 15}, {"RAM", 20}, };
    //     int val;
    // std::map<int, int> std_map;
    // ft::map<int, int> ft_map;

    // std::cout << GREEN << "FT  map empty: " << RESET << ft_map.empty() << std::endl;
	// std::cout << GREEN << "STD map empty: " << RESET << std_map.empty() << std::endl << std::endl;

	// std::cout << GREEN << "FT  map size: " << RESET << ft_map.size() << std::endl;
	// std::cout << GREEN << "STD map size: " << RESET << std_map.size() << std::endl << std::endl;

    // std::cout << GREEN << "Map elem: " << RESET;
    // for (int i = 0; i <= 10; i++) {
    //     val = rand() % 10;
    //     std_map[i] = val;
    //     ft_map[i] = val;
    //     std::cout << val << " ";
    // }
    // std::cout << std::endl << std::endl;

    // std::cout << GREEN << "FT  map size: " << RESET << ft_map.size() << std::endl;
	// std::cout << GREEN << "STD map size: " << RESET << std_map.size() << std::endl << std::endl;

    // //std::cout << GREEN << "FT  map max size: " << RESET << ft_map.max_size() << std::endl;
	// //std::cout << GREEN << "STD map max size: " << RESET << ft_map.max_size() << std::endl;

	// std::cout << RED << LINE << RESET << std::endl << std::endl;

    int val;
    std::map<int, int> std_map;
    ft::map<int, int> ft_map;

    std::cout << GREEN << "Map elem: " << RESET;
    for (int i = 0; i <= 10; i++) {
        val = rand() % 10;
        std_map[i] = val;
        ft_map[i] = val;
        std::cout << val << " ";
    }
    std::cout << std::endl << std::endl;
	/////////////////////////////////////////////////////////////////////////
    std::cout << GREEN << "FT  iterator: " << RESET;
	ft::map<int, int>::iterator ft_it = ft_map.begin();
	for (;ft_it != ft_map.end(); ++ft_it) {
		std::cout << "[" << ft_it->first << "]" << " " << ft_it->second << " | ";
	}
	std::cout << GREEN << "\nSTD iterator: " << RESET;
	std::map<int, int>::iterator std_it = std_map.begin();
	for (;std_it != std_map.end(); ++std_it) {
		std::cout << "[" << std_it->first << "]" << " " << std_it->second << " | ";
	}
	std::cout << std::endl << std::endl;
	/////////////////////////////////////////////////////////////////////////
    std::cout << GREEN << "FT  reverse iterator: " << RESET;
	ft::map<int, int>::reverse_iterator ft_rit = ft_map.rbegin();
	for (;ft_rit != ft_map.rend(); ++ft_rit) {
		std::cout << "[" << ft_rit->first << "]" << " " << ft_rit->second << " | ";
	}
	std::cout << GREEN << "\nSTD reverse iterator: " << RESET;
	std::map<int, int>::reverse_iterator std_rit = std_map.rbegin();
	for (;std_rit != std_map.rend(); ++std_rit) {
		std::cout << "[" << std_rit->first << "]" << " " << std_rit->second << " | ";
	}
	/////////////////////////////////////////////////////////////////////////
	std::cout << std::endl << RED << LINE << RESET << std::endl;
	std::cout << std::endl;
    // //bst.delete_(25);
    //bst.prettyPrint();
    return 0;
}
