#ifndef __SRCS_SET_TEST_HPP
#define __SRCS_SET_TEST_HPP

#include <set>

#include "../set.hpp"
#include "../utils/algorithm.hpp"
#include "utils.hpp"

#define ITERATIONS 1000

template<class T>
void    show_ft_set(ft::set<T> set) {
    typename ft::set<T>::iterator    it = set.begin();

    while (it != set.end()) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "--> ft\n";
}

template<class T>
void    show_std_set(std::set<T> set) {
    typename std::set<T>::iterator    it = set.begin();

    while (it != set.end()) {
        std::cout << *it << " ";
        it++;
    }
    std::cout << "--> std\n";
}

void call_tests();
#endif /* ifndef __SRCS_SET_TEST_HPP */
