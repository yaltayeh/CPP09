#pragma once

#include <vector>
#include "IntWrapper.hpp"

struct Pair
{
    int level;
    IntWrapper value;
    IntWrapper partner;

    Pair(int l, IntWrapper v, IntWrapper p) : level(l), value(v), partner(p) {}
};

class PmergeMe
{
private:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);

public:
    template <typename Container>
    static typename Container::iterator binarySearch(Container &chain, typename Container::value_type element, typename Container::iterator it_limit);
    template <typename Container>
    static void binaryInsert(Container &chain, typename Container::value_type element, typename Container::iterator limit);

    template <typename Container>
    static size_t sort(Container &input);
};

#include "PmergeMe.tpp"