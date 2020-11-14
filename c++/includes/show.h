#ifndef SHOW_H
#define SHOW_H

#include <iostream>


template <typename T>
void print_range(const T &v)
{
    std::cout << '{';
    auto i{v.begin()};
    if (i != v.end())
        std::cout << *i++;
    for (; i != v.end(); ++i)
        std::cout << ", " << *i;
    std::cout << '}' << std::endl;
}

template <typename Iter>
void print_range(const Iter &begin, const Iter &end)
{
    std::cout << '[';
    auto i{begin};
    if (i < end)
        std::cout << *i++;
    for (; i < end; ++i)
        std::cout << ", " << *i;
    std::cout << ']' << std::endl;
}

#endif // SHOW_H
