#include "PmergeMe.hpp"

template <typename T>
PmergeMe<T>::PmergeMe() : data() {}

template <typename T>
PmergeMe<T>::~PmergeMe() {}

template <typename T>
PmergeMe<T>::PmergeMe(const T& initialData) : data(initialData) {}

template <typename T>
PmergeMe<T>::PmergeMe(const PmergeMe &other) : data(other.data) {}

template <typename T>
PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        data = other.data;
    }
    return *this;
}

template <typename T>
T & PmergeMe<T>::getData()
{
    return data;
}

template <typename T>
const T & PmergeMe<T>::getData() const
{
    return data;
}


template <typename T>
void PmergeMe<T>::sort()
{
    
}

template <typename T>
void PmergeMe<T>::sort(T &container)
{
    std::sort(container.begin(), container.end());
}
