#include "set_test.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <set>

template <class Input1, class Input2>
bool compare_sets(Input1 beg1, Input1 end, Input2 beg2) {
    while (beg1 != end) {
        if (*beg1 != *beg2) return false;
        beg1++;
        beg2++;
    }
    return true;
}

void compare_set(std::set<int> std_map, ft::set<int> ft_map) {
    bool equal;

    equal = compare_sets(std_map.begin(), std_map.end(), ft_map.begin());
    std::cout << "content: ";
    checker(equal);
    // if (!equal) show_map(ft_map);

    equal = std_map.size() == ft_map.size();
    std::cout << "size: ";
    checker(equal);
    std::cout << "\n";
    if (!equal)
        std::cout << "std: " << std_map.size() << "\t"
                  << "ft: " << ft_map.size() << "\n";
}

void constructor_test_1() {
    test_title("default constructor test 1");
    std::set<int>   std_set;
    ft::set<int>   ft_set;

    compare_set(std_set, ft_set);
}

void constructor_test_2() {
    test_title("default constructor test 2");
    std::allocator<int> alloc;
    std::less<int> comp;
    std::set<int>   std_set(comp, alloc);
    ft::set<int>   ft_set(comp, alloc);

    compare_set(std_set, ft_set);
}

void constructor_test_3() {
    test_title("range constructor test 3");
    std::set<int>   std_buf;
    ft::set<int>   ft_buf;

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_buf.insert(i);
        ft_buf.insert(i);
    }

    std::set<int>   std_set(std_buf.begin(), std_buf.end());
    ft::set<int>   ft_set(ft_buf.begin(), ft_buf.end());

    compare_set(std_set, ft_set);
}

void constructor_test_4() {
    test_title("copy constructor test 3");
    std::set<int>   std_buf;
    ft::set<int>   ft_buf;

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_buf.insert(i);
        ft_buf.insert(i);
    }

    std::set<int>   std_set(std_buf);
    ft::set<int>   ft_set(ft_buf);
    compare_set(std_set, ft_set);

    std::set<int>   std_set1 = std_buf;
    ft::set<int>   ft_set1 = ft_buf;
    compare_set(std_set1, ft_set1);

    test_title("empty copy");
    std::set<int>   std_set2;
    ft::set<int>   ft_set2;
    std::set<int>   std_set3(std_set2);
    ft::set<int>   ft_set3(ft_set2);
    compare_set(std_set3, ft_set3);
}

void assign_test_1() {
    test_title("assign test 1");
    std::set<int>   std_buf;
    ft::set<int>   ft_buf;

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_buf.insert(i);
        ft_buf.insert(i);
    }
    std::set<int>   std_set;
    ft::set<int>   ft_set;

    std_set = std_buf;
    ft_set = ft_buf;

    compare_set(std_set, ft_set);
}

void assign_test_2() {
    test_title("assign test 2");
    std::set<int>   std_buf;
    ft::set<int>   ft_buf;

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_buf.insert(i);
        ft_buf.insert(i);
    }
    std::set<int>   std_set;
    ft::set<int>   ft_set;

    std_buf.clear();
    std_set = std_buf;
    ft_buf.clear();
    ft_set = ft_buf;

    compare_set(std_set, ft_set);
}

void capacity_test() {
    test_title("capacity test 1");

    std::set<int>   std_set;
    ft::set<int>   ft_set;

    checker(std_set.size() == ft_set.size());
    checker(std_set.empty() == ft_set.empty());

    test_title("capacity test 2");
    std_set.insert(1);
    ft_set.insert(1);

    checker(std_set.size() == ft_set.size());
    checker(std_set.empty() == ft_set.empty());

    test_title("capacity test 3");
    checker(std_set.erase(1) == ft_set.erase(1));
    checker(std_set.size() == ft_set.size());
    checker(std_set.empty() == ft_set.empty());

    test_title("capacity test 4");

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }
    checker(std_set.size() == ft_set.size());
    checker(std_set.empty() == ft_set.empty());

    test_title("capacity test 4");

    std_set.erase(++std_set.begin(), --std_set.end());
    ft_set.erase(++ft_set.begin(), --ft_set.end());
    checker(std_set.size() == ft_set.size());
    checker(std_set.empty() == ft_set.empty());
}

void modifiers_test() {
    test_title("\ninsert test 1");

    std::set<int>   std_set;
    ft::set<int>   ft_set;

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }
    compare_set(std_set, ft_set);

    std_set.clear();
    ft_set.clear();

    test_title("insert test 2");
    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(std_set.begin(), i);
        ft_set.insert(ft_set.begin(), i);
    }
    compare_set(std_set, ft_set);

    std_set.clear();
    ft_set.clear();

    test_title("insert test 3");
    std::set<int>   std_buf;
    ft::set<int>   ft_buf;

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_buf.insert(i);
        ft_buf.insert(i);
    }

    std_set.insert(std_buf.begin(), std_buf.end());
    ft_set.insert(ft_buf.begin(), ft_buf.end());
    compare_set(std_set, ft_set);

    std_set.clear();
    ft_set.clear();

    test_title("insert test 4");
    std_set.insert(++std_buf.begin(), --std_buf.end());
    ft_set.insert(++ft_buf.begin(), --ft_buf.end());
    compare_set(std_set, ft_set);

    test_title("erase test 1");
    std_set.erase(1);
    ft_set.erase(1);
    compare_set(std_set, ft_set);

    test_title("erase test 2");
    std_set.erase(std_set.begin());
    ft_set.erase(ft_set.begin());
    compare_set(std_set, ft_set);

    test_title("erase test 3");
    std_set.erase(--std_set.end());
    ft_set.erase(--ft_set.end());
    compare_set(std_set, ft_set);

    test_title("erase test 4");
    std_set.erase(std_set.begin(), std_set.end());
    ft_set.erase(ft_set.begin(), ft_set.end());
    compare_set(std_set, ft_set);
    checker(std_set.empty() == ft_set.empty());
    std_set.clear();
    ft_set.clear();
    checker(std_set.empty() == ft_set.empty());

    test_title("erase test 5");
    std_set.insert(1);
    ft_set.insert(1);
    checker(std_set.erase(1) == ft_set.erase(1));
    checker(std_set.erase(0) == ft_set.erase(0));
    compare_set(std_set, ft_set);

    test_title("swap test 1");
    std_buf.clear();
    ft_buf.clear();
    compare_set(std_buf, ft_buf);

    std_set.swap(std_buf);
    ft_set.swap(ft_buf);
    compare_set(std_set, ft_set);

    test_title("swap test 2");
    std_set.insert(10);
    ft_set.insert(10);
    std_set.swap(std_buf);
    ft_set.swap(ft_buf);
    compare_set(std_set, ft_set);

    test_title("swap test 3");
    std_buf.clear();
    ft_buf.clear();
    std_set.clear();
    ft_set.clear();
    std_set.swap(std_buf);
    ft_set.swap(ft_buf);
    compare_set(std_set, ft_set);
}

void operation_test() {
    std::set<int>   std_set;
    ft::set<int>   ft_set;

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }
    test_title("find test 1");

    checker(*std_set.find(1) == *ft_set.find(1));
    checker(*std_set.find(ITERATIONS + 1) == *ft_set.find(ITERATIONS + 1));

    test_title("find test 2");
    std_set.clear();
    ft_set.clear();
    checker(*std_set.find(1) == *ft_set.find(1));
    checker(*std_set.find(ITERATIONS + 1) == *ft_set.find(ITERATIONS + 1));

    test_title("count test 1");
    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }
    checker(std_set.count(1) == ft_set.count(1));
    checker(std_set.count(ITERATIONS + 1) == ft_set.count(ITERATIONS + 1));

    test_title("count test 2");
    std_set.clear();
    ft_set.clear();
    checker(std_set.count(1) == ft_set.count(1));
    checker(std_set.count(ITERATIONS + 1) == ft_set.count(ITERATIONS + 1));

    std_set.clear();
    ft_set.clear();

    test_title("lower_bound test 1");
    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }

    checker(*std_set.lower_bound(1) == *ft_set.lower_bound(1));
    checker(*std_set.lower_bound(ITERATIONS + 1) == *ft_set.lower_bound(ITERATIONS + 1));

    test_title("lower_bound test 2");
    std_set.clear();
    ft_set.clear();
    checker(*std_set.lower_bound(1) == *ft_set.lower_bound(1));
    checker(*std_set.lower_bound(ITERATIONS + 1) == *ft_set.lower_bound(ITERATIONS + 1));

    std_set.clear();
    ft_set.clear();

    test_title("upper_bound test 1");
    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }

    checker(*std_set.upper_bound(1) == *ft_set.upper_bound(1));
    checker(*std_set.upper_bound(ITERATIONS + 1) == *ft_set.upper_bound(ITERATIONS + 1));

    test_title("upper_bound test 2");
    std_set.clear();
    ft_set.clear();
    checker(*std_set.upper_bound(1) == *ft_set.upper_bound(1));
    checker(*std_set.upper_bound(ITERATIONS + 1) == *ft_set.upper_bound(ITERATIONS + 1));

    std_set.clear();
    ft_set.clear();

    test_title("lower/upper test 1");

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }
    std_set.erase(std_set.lower_bound(1), std_set.lower_bound(10));
    ft_set.erase(ft_set.lower_bound(1), ft_set.lower_bound(10));
    compare_set(std_set, ft_set);
    checker(std_set.size() == ft_set.size());

    test_title("lower/upper test 2");
    std_set.erase(std_set.upper_bound(1), std_set.upper_bound(10));
    ft_set.erase(ft_set.upper_bound(1), ft_set.upper_bound(10));
    compare_set(std_set, ft_set);
    checker(std_set.size() == ft_set.size());

    std_set.clear();
    ft_set.clear();

    test_title("lower/upper test 3");

    for (size_t i = 0; i < ITERATIONS; i++) {
        std_set.insert(i);
        ft_set.insert(i);
    }
    std_set.erase(std_set.lower_bound(1), std_set.upper_bound(ITERATIONS + 10));
    ft_set.erase(ft_set.lower_bound(1), ft_set.upper_bound(ITERATIONS + 10));
    compare_set(std_set, ft_set);
    checker(std_set.size() == ft_set.size());
}

void mixup() {
    std::set<int>   std_set;
    ft::set<int>   ft_set;
    int r_num;
    srand(time(0));

    test_title("mixup test 1");
    for (size_t i = 0; i < 10; i++) {
        r_num = rand() % 10;
        std_set.insert(r_num);
        ft_set.insert(r_num);
    }
    show_std_set(std_set);
    show_ft_set(ft_set);
    compare_set(std_set, ft_set);

    test_title("mixup test 2");
    std_set.erase(1);
    ft_set.erase(1);
    show_std_set(std_set);
    show_ft_set(ft_set);
    compare_set(std_set, ft_set);

    test_title("mixup test 3");
    std::set<int>   std_set1(std_set);
    ft::set<int>   ft_set1(ft_set);
    show_std_set(std_set1);
    show_ft_set(ft_set1);
    compare_set(std_set1, ft_set1);

    test_title("mixup test 3");
    std_set1.clear();
    ft_set1.clear();
    show_std_set(std_set1);
    show_ft_set(ft_set1);
    compare_set(std_set1, ft_set1);
}

void call_tests() {
    constructor_test_1();
    constructor_test_2();
    constructor_test_3();
    constructor_test_4();
    assign_test_1();
    assign_test_2();
    capacity_test();
    modifiers_test();
    operation_test();
    mixup();
}
