#include "map_test.hpp"

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>

#include "utils.hpp"

template <class Key, class T>
void show_map(ft::map<Key, T> &map) {
    typename ft::map<Key, T>::iterator it = map.begin();

    std::cout << "[ " << std::addressof(map) << " ]"
              << "\n";
    for (; it != map.end(); it++) {
        std::cout << it->first << " ";
    }
    std::cout << "\n";
}

ft::pair<int, char> ft_rand_pair() {
    ft::pair<int, char> par;

    par = ft::make_pair(rand() % ITER, static_cast<char>(65 + (rand() % 25)));
    return (par);
}

std::pair<int, char> std_rand_pair() {
    std::pair<int, char> par;

    par = std::make_pair(rand() % ITER, static_cast<char>(65 + (rand() % 25)));
    return (par);
}

ft::pair<int, char> ft_pair(int num) {
    ft::pair<int, char> par;

    par = ft::make_pair(num, 65 + num);
    return (par);
}

std::pair<int, char> std_pair(int num) {
    std::pair<int, char> par;

    par = std::make_pair(num, 65 + num);
    return (par);
}

template <class Input1, class Input2>
bool compare_sets(Input1 beg1, Input1 end, Input2 beg2) {
    while (beg1 != end) {
        if (beg1->first != beg2->first) return false;
        beg1++;
        beg2++;
    }
    return true;
}

void compare_maps(std::map<int, char> std_map, ft::map<int, char> ft_map) {
    bool equal;

    equal = compare_sets(std_map.begin(), std_map.end(), ft_map.begin());
    std::cout << "content: ";
    checker(equal);
    if (!equal) show_map(ft_map);

    equal = std_map.size() == ft_map.size();
    std::cout << "size: ";
    checker(equal);
    std::cout << "\n";
    if (!equal)
        std::cout << "std: " << std_map.size() << "\t"
                  << "ft: " << ft_map.size() << "\n";
}

void constructor_tests() {
    int start;
    int end;
    int std_ticks;
    int ft_ticks;

    std::pair<int, char> std[] = {std_pair(0), std_pair(10), std_pair(23),
                                  std_pair(1), std_pair(2),  std_pair(3)};
    ft::pair<int, char> ft[] = {ft_pair(0), ft_pair(10), ft_pair(23),
                                ft_pair(1), ft_pair(2),  ft_pair(3)};

    test_title("CONSTRUTOR TEST");

    start = clock();
    std::map<int, char> std_map(std, std + 6);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    std_ticks = end - start;

    start = clock();
    ft::map<int, char> ft_map(ft, ft + 6);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    test_title("ITERATOR TEST");

    std::map<int, char> big_map;
    ft::map<int, char> ft_big_map;

    for (size_t i = 0; i < ITER; i++) {
        big_map.insert(std_pair(i));
        ft_big_map.insert(ft_pair(i));
    }
    std::cout << "STD:\t";
    start = clock();
    std::map<int, char> std_map1(big_map.lower_bound(10),
                                 big_map.upper_bound(500));
    end = clock();
    time(start, end);
    std_ticks = end - start;

    std::cout << "FT:\t";
    start = clock();
    ft::map<int, char> ft_map1(ft_big_map.lower_bound(10),
                               ft_big_map.upper_bound(500));
    end = clock();
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    test_title("CLEAR CHECK");

    checker(ft_map1.empty() == std_map1.empty());

    test_title("COPY TEST");

    std::cout << "STD:\t";
    start = clock();
    std::map<int, char> std_map2(big_map);
    end = clock();
    time(start, end);
    std_ticks = end - start;

    std::cout << "FT:\t";
    start = clock();
    ft::map<int, char> ft_map2(ft_big_map);
    end = clock();
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    test_title("CLEAR TEST");

    checker(ft_map2.empty() == std_map2.empty());
}

void insert_test() {
    int start;
    int end;
    int std_ticks;
    int ft_ticks;
    ft::map<int, char> ft_map;
    std::map<int, char> std_map;

    test_title("INSERT CONTINUOUSLY TEST");
    start = clock();
    for (size_t i = 0; i < ITER; i++) {
        std_map.insert(std_pair(i));
    }
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    std_ticks = end - start;

    start = clock();
    for (size_t i = 0; i < ITER; i++) {
        ft_map.insert(ft_pair(i));
    }
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    test_title("INSERT EXISTED TEST");
    ft_map.insert(ft_pair(10));
    std_map.insert(std_pair(10));

    compare_maps(std_map, ft_map);

    test_title("INSERT POSITION TEST");
    ft_map.insert(ft_map.begin(), ft_pair(1600));
    std_map.insert(std_map.begin(), std_pair(1600));

    compare_maps(std_map, ft_map);
    /**************************************/

    ft::map<int, char>::iterator ft_it = ft_map.begin();
    std::map<int, char>::iterator std_it = std_map.begin();
    for (int i = 0; i < 5; i++) ft_it++;

    std::advance(std_it, 5);
    ft_map.insert(ft_it, ft_pair(1600));
    std_map.insert(std_it, std_pair(1600));

    compare_maps(std_map, ft_map);
    ft_map.clear();
    std_map.clear();

    test_title("INSERT ITERATORS TEST");

    ft::map<int, char> ft_buf;
    std::map<int, char> std_buf;
    int i = 0;
    while (i < ITER) {
        ft_buf.insert(ft_pair(i));
        std_buf.insert(std_pair(i));
        i++;
    }

    start = clock();
    std_map.insert(std_buf.lower_bound(10), std_buf.upper_bound(150));
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    std_ticks = end - start;

    start = clock();
    ft_map.insert(ft_buf.lower_bound(10), ft_buf.upper_bound(150));
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    ft_map.clear();
    std_map.clear();

    test_title("OPERATOR[] TEST");
    i = -1;
    start = clock();
    while (++i < 150) std_map[i] = 65 + i;
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    ft_ticks = end - start;

    i = -1;
    start = clock();
    while (++i < 150) ft_map[i] = 65 + i;
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    ft_map.clear();
    std_map.clear();
}

void erase_test() {
    int start;
    int end;
    int std_ticks;
    int ft_ticks;
    ft::map<int, char> ft_map;
    std::map<int, char> std_map;

    for (int i = 0; i < ITER; i++) {
        ft_map.insert(ft_pair(i));
        std_map.insert(std_pair(i));
    }

    test_title("ERASE SINGLE ELEMENT");
    start = clock();
    std_map.erase(10);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    std_ticks = end - start;

    start = clock();
    ft_map.erase(10);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    test_title("ERASE NOT EXISTING ELEMENT");

    start = clock();
    std_map.erase(ITER + 1);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    std_ticks = end - start;

    start = clock();
    ft_map.erase(ITER + 1);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    test_title("ERASE RANGE");

    std_map.erase(25);
    ft_map.erase(25);

    start = clock();
    std_map.erase(std_map.lower_bound(10), std_map.upper_bound(25));
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    std_ticks = end - start;

    start = clock();
    ft_map.erase(ft_map.lower_bound(10), ft_map.upper_bound(25));
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    test_title("ERASE POSITION");

    ft::map<int, char>::iterator ft_it = ft_map.begin();
    std::map<int, char>::iterator std_it = std_map.begin();

    start = clock();
    std_map.erase(std_it);
    std_it = std_map.begin();
    std_map.erase(++std_it);
    std_it = std_map.end();
    std_map.erase(--std_it);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);
    std_ticks = end - start;

    start = clock();
    ft_map.erase(ft_it);
    ft_it = ft_map.begin();
    ft_map.erase(++ft_it);
    ft_it = ft_map.end();
    ft_map.erase(--ft_it);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);
    ft_ticks = end - start;

    percentage_compare(std_ticks, ft_ticks);
    compare_maps(std_map, ft_map);

    ft::map<int, char> ft_map2;
    std::map<int, char> std_map2;

    std_map2.erase(10);
    ft_map2.erase(10);
    compare_maps(std_map, ft_map);
}

void find_test() {
    int start;
    int end;
    ft::map<int, char> ft_map;
    std::map<int, char> std_map;

    for (int i = 0; i < ITER; i++) {
        ft_map.insert(ft_pair(i));
        std_map.insert(std_pair(i));
    }

    test_title("FIND");
    ft::map<int, char>::iterator ft_it;
    std::map<int, char>::iterator std_it;

    start = clock();
    std_it = std_map.find(1);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    start = clock();
    ft_it = ft_map.find(1);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    checker((ft_it->first == std_it->first && ft_it->second == std_it->second));
    test_title("FIND ERASED");
    ft_map.erase(1);
    std_map.erase(1);

    start = clock();
    std_it = std_map.find(1);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    start = clock();
    ft_it = ft_map.find(1);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    checker((ft_it == ft_map.end() && std_it == std_map.end()));

    test_title("FIND IN EMPTY MAP");
    ft::map<int, char> ft_map1;
    std::map<int, char> std_map1;

    start = clock();
    std_it = std_map1.find(1);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    start = clock();
    ft_it = ft_map1.find(1);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    checker((ft_it == ft_map1.end() && std_it == std_map1.end()));
}

void lower_upper_bound() {
    int start;
    int end;
    ft::map<int, char> ft_map;
    std::map<int, char> std_map;
    ft::map<int, char>::iterator ft_it;
    std::map<int, char>::iterator std_it;

    for (int i = 0; i < ITER; i++) {
        ft_map.insert(ft_pair(i));
        std_map.insert(std_pair(i));
    }

    test_title("LOWER BOUND");

    start = clock();
    std_it = std_map.lower_bound(10);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    start = clock();
    ft_it = ft_map.lower_bound(10);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    checker((ft_it->first == std_it->first && ft_it->second == std_it->second));

    test_title("LOWER ON ERASED");

    std_map.erase(10);
    ft_map.erase(10);

    start = clock();
    std_it = std_map.lower_bound(10);
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    start = clock();
    ft_it = ft_map.lower_bound(10);
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    checker((ft_it->first == std_it->first && ft_it->second == std_it->second));

    test_title("COMPARE WITH LOWER");
    checker(compare_sets(std_map.lower_bound(10), std_map.lower_bound(500),
                         ft_map.lower_bound(10)));

    test_title("ERASE WITH LOWER");

    start = clock();
    std_map.erase(std_map.lower_bound(1), std_map.lower_bound(10));
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    start = clock();
    ft_map.erase(ft_map.lower_bound(1), ft_map.lower_bound(10));
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    compare_maps(std_map, ft_map);

    test_title("INSERT EXISTED");

    start = clock();
    std_map.insert(std_map.lower_bound(25), std_map.lower_bound(60));
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    start = clock();
    ft_map.insert(ft_map.lower_bound(25), ft_map.lower_bound(60));
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    compare_maps(std_map, ft_map);

    test_title("INSERT FROM BUFFER");

    std::map<int, char> std_buffer;
    ft::map<int, char> ft_buffer;

    for (int i = 0; i < ITER; i++) {
        std_buffer.insert(std_pair(i));
        ft_buffer.insert(ft_pair(i));
    }

    std_buffer.erase(250);
    start = clock();
    std_map.insert(std_buffer.lower_bound(10), std_buffer.upper_bound(230));
    end = clock();
    std::cout << "STD:\t";
    time(start, end);

    ft_buffer.erase(250);
    start = clock();
    ft_map.insert(ft_buffer.lower_bound(10), ft_buffer.upper_bound(230));
    end = clock();
    std::cout << "FT:\t";
    time(start, end);

    compare_maps(std_map, ft_map);
}

void mixup() {
    ft::map<int, char> ft_m1;
    ft::map<int, char> ft_m2;
    std::map<int, char> std_m1;

    test_title("MIXUP");

    checker(ft_m1.size() == std_m1.size());
    for (int i = 0; i < ITER; i++) ft_m1.insert(ft_pair(i));

    checker(ft_m1.max_size() == std_m1.max_size());
    checker(ft_m1.size() == ITER);
    ft_m1.insert(ft_pair(1));
    checker(ft_m1.size() == ITER);
    ft_m1.insert(ft_pair(ITER + 1));
    checker(ft_m1.size() == ITER + 1);
    ft_m1.erase(1);
    checker(ft_m1.size() == ITER);
    ft_m1.erase(ft_m1.lower_bound(10), ft_m1.lower_bound(25));
    checker(ft_m1.size() == ITER - 15);

    ft_m2 = ft_m1;
    checker(ft_m1.size() == ft_m2.size());
    checker(ft::equal(ft_m1.begin(), ft_m1.end(), ft_m2.begin()));

    ft_m1[2] = 'c';
    ft_m2[2] = 'c';
    checker(ft::equal(ft_m1.begin(), ft_m1.end(), ft_m2.begin()));

    ft_m1[ITER + 1] = 'c';
    ft_m2[ITER + 1] = 'c';
    checker(ft::equal(ft_m1.begin(), ft_m1.end(), ft_m2.begin()));

    ft_m1.erase(ft_m1.begin(), ft_m1.end());
    checker(ft_m1.size() == 0);
    checker(!ft::equal(ft_m2.begin(), ft_m2.end(), ft_m1.begin()));

    ft_m1.clear();
    ft_m2.clear();
    checker(ft_m1.size() == ft_m2.size());

    ft_m1.insert(ft_pair(1));
    ft_m2.insert(ft_pair(1));
    checker(*ft_m1.find(1) == *ft_m2.find(1));

    for (int i = 0; i < 15; i++) {
        ft_m1.insert(ft_pair(i));
        ft_m2.insert(ft_pair(i));
    }
    checker(*ft_m1.lower_bound(10) == *ft_m2.lower_bound(10));
    checker(*ft_m1.upper_bound(10) == *ft_m2.upper_bound(10));
    checker(*ft_m1.lower_bound(15) == *ft_m2.lower_bound(15));
    checker(*ft_m1.upper_bound(15) == *ft_m2.upper_bound(15));

    ft_m1.erase(15);
    ft_m2.erase(15);
    checker(*ft_m1.lower_bound(15) == *ft_m2.lower_bound(15));
    checker(*ft_m1.upper_bound(15) == *ft_m2.upper_bound(15));
    checker(ft_m1.count(1) == ft_m2.count(1));
    checker(ft_m1.count(16) == ft_m2.count(16));
    ft_m1.swap(ft_m2);
    checker(ft_m1.size() == ft_m2.size());
    checker(ft::equal(ft_m2.begin(), ft_m2.end(), ft_m1.begin()));

    ft_m2.erase(1);
    ft_m1.swap(ft_m2);
    checker(!(ft_m1.size() == ft_m2.size()));
    checker(!ft::equal(ft_m2.begin(), ft_m2.end(), ft_m1.begin()));

    ft_m1.clear();
    ft_m2.clear();
    ft_m1.swap(ft_m2);
    checker((ft_m1.size() == ft_m2.size()));
    checker(ft::equal(ft_m2.begin(), ft_m2.end(), ft_m1.begin()));

    for (int i = 0; i < 15; i++) {
        ft_m1.insert(ft_pair(i));
        ft_m2.insert(ft_pair(i));
    }
    ft::map<int, char>::iterator ft_beg1 = ft_m1.begin();
    ft::map<int, char>::iterator ft_beg2 = ft_m2.begin();
    ft::map<int, char>::iterator ft_end1 = ft_m1.end();
    ft::map<int, char>::iterator ft_end2 = ft_m2.end();
    ft::map<int, char>::reverse_iterator ft_rbeg1 = ft_m1.rbegin();
    ft::map<int, char>::reverse_iterator ft_rbeg2 = ft_m2.rbegin();
    ft::map<int, char>::reverse_iterator ft_rend1 = ft_m1.rend();
    ft::map<int, char>::reverse_iterator ft_rend2 = ft_m2.rend();

    checker(*ft_m1.begin() == *ft_m2.begin());
    checker(*ft_m1.end() == *ft_m2.end());
    checker(*ft_m1.rbegin() == *ft_m2.rbegin());
    checker(*ft_m1.rend() == *ft_m2.rend());

    ft_beg1++;
    ft_beg2++;
    checker(*ft_beg1 == *ft_beg2);

    ft_end1--;
    ft_end2--;
    checker(*ft_end1 == *ft_end2);

    ft_rbeg1--;
    ft_rbeg2--;
    checker(*ft_rbeg1 == *ft_rbeg2);

    ft_rend1++;
    ft_rend2++;
    checker(*ft_rend1 == *ft_rend2);
}

void    swap() {
    test_title("SWAP");
    std::map<int, char> std_m1;
    ft::map<int, char> ft_m1;
    std::map<int, char> std_m2;
    ft::map<int, char> ft_m2;

    for (size_t i = 0; i < 10; i++) {
        std_m1.insert(std_pair(i));
        ft_m1.insert(ft_pair(i));
    }

    std_m1.swap(std_m2);
    ft_m1.swap(ft_m2);

    compare_maps(std_m2, ft_m2);
    compare_maps(std_m1, ft_m1);

    std_m1.clear();
    ft_m1.clear();
    for (size_t i = 0; i < ITER; i++) {
        std_m1.insert(std_pair(i));
        ft_m1.insert(ft_pair(i));
    }

    std_m1.swap(std_m2);
    ft_m1.swap(ft_m2);
    compare_maps(std_m2, ft_m2);
    compare_maps(std_m1, ft_m1);

    std_m2.erase(std_m2.lower_bound(10), std_m2.upper_bound(90));
    std_m2.swap(std_m1);
    ft_m2.erase(ft_m2.lower_bound(10), ft_m2.upper_bound(90));
    ft_m2.swap(ft_m1);
    compare_maps(std_m2, ft_m2);
    compare_maps(std_m1, ft_m1);
}

void key_comp() {

    std::map<int, long> smap;
    ft::map<int, long> fmap;

    // stress_test(smap, fmap);

    std::cout << fmap.key_comp()(5, 2);
    // if (smap.key_comp()(5, 2) != fmap.key_comp()(5, 2))
    //     std::cout << RED "KO" DEFAULT << " " << std::flush;
    // else
    //     std::cout << GREEN "OK" DEFAULT << " " << std::flush;

    // std::cout << "hello";
    // if (smap.key_comp()(1, 2) != fmap.key_comp()(1, 2))
    //     std::cout << RED "KO" DEFAULT << " " << std::flush;
    // else
    //     std::cout << GREEN "OK" DEFAULT << " " << std::flush;

    // if (smap.key_comp()(5, 5) != fmap.key_comp()(5, 5))
    //     std::cout << RED "KO" DEFAULT << "\n" << std::endl;
    // else
    //     std::cout << GREEN "OK" DEFAULT << "\n" << std::endl;
}
