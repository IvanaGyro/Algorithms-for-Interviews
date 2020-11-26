#ifndef TEST_H
#define TEST_H

#include <initializer_list>
#include <iostream>
#include <cassert>
#include "show.h"


#define test(proc, ans...) \
    std::cout << "test " << CASE_NO++ << ": "#proc << std::endl; \
    std::cout << "answer: "#ans << std::endl; \
    _test(proc, ans); \
    std::cout << "-----" << std::endl;

int CASE_NO {1};

template<typename T, typename V>
void _test(const T& container, std::initializer_list<V> list) {
    std::cout << "input: " << container << std::endl;
    assert(container.size() == list.size());
    auto begin_c {container.begin()};
    auto begin_l {list.begin()};
    while (begin_c != container.end()) {
        assert(*begin_c++ == *begin_l++);
    }
}

template<typename T>
void _test(const T& a, const T& b) {
    std::cout << "input: " << a << std::endl;
    assert(a == b);
}

#endif // TEST_H
