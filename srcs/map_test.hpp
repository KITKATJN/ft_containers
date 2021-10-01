#ifndef __SRCS_MAP_TEST_HPP__
#define __SRCS_MAP_TEST_HPP__

#include <map>

#include "../ft_containers/map.hpp"
#include "utils.hpp"

#define ITER 15000

ft::pair<int, char> ft_rand_pair();
ft::pair<int, char> ft_pair(int num);
std::pair<int, char> std_pair(int num);

void insert_test();
void constructor_tests();
void erase_test();
void find_test();
void lower_upper_bound();
void mixup();
void swap();
void ft_map_tests();
void key_comp();

#endif /* ifndef __SRCS_MAP_TEST_HPP__ */
