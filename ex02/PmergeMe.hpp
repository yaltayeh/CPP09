#pragma once

template <typename T>
class PmergeMe
{
private:
    T &data;
    
    void sort(T &container);

public:
    PmergeMe();
    PmergeMe(const T& initialData);
    ~PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe& operator=(const PmergeMe &other);

    T & getData();
    const T & getData() const;

    void sort();
};

#include "PmergeMe.tpp"
