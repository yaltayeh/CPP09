#include "PmergeMe.hpp"
#include <deque>
#include <algorithm>
#include <iostream>
#include <list>
#include "Jacobsthal.hpp"

template <typename Container>
typename Container::iterator PmergeMe::binarySearch(Container &chain, typename Container::value_type element, typename Container::iterator it_limit)
{	typename Container::iterator pos = std::lower_bound(chain.begin(), it_limit, element);
	it_limit = pos;
	return pos;
}

template <typename Container>
void PmergeMe::binaryInsert(Container &chain, typename Container::value_type element, typename Container::iterator limit)
{
	typename Container::iterator pos = binarySearch(chain, element, limit);
	chain.insert(pos, element);
}

template <typename Container>
size_t PmergeMe::sort(Container &main_chain)
{
	std::deque<Pair> tmp;

	int level = 0;
	while (main_chain.size() > 1)
	{
		typename Container::iterator it;
		typename Container::iterator next;
		for (it = main_chain.begin(); it != main_chain.end(); ++it)
		{
			next = std::next(it);
			if (next != main_chain.end())
			{
				Pair p(level, *it, *next);
				if (*it < *next)
				{
					it = main_chain.erase(it);
				}
				else
				{
					std::swap(p.value, p.partner);
					main_chain.erase(next);
				}
				tmp.push_back(p);
			}
		}
		level++;
	}

	while (!tmp.empty())
	{
		std::deque<Pair> pinneds;
		level = tmp.back().level;
		while (!tmp.empty() && tmp.back().level == level)
		{
			pinneds.push_back(tmp.back());
			tmp.pop_back();
		}
		while (!pinneds.empty())
		{
			Jacobsthal jacob;
			unsigned int idx = jacob.next();
			for (; idx < pinneds.size();)
			{
				Pair p = *std::next(pinneds.begin(), idx);
				pinneds.erase(std::next(pinneds.begin(), idx));
				if (p.partner != -1)
				{
					typename Container::iterator it_limit = main_chain.end();
					if (p.partner != -1)
						it_limit = binarySearch(main_chain, p.partner, it_limit);

					binaryInsert(main_chain, p.value, it_limit);
				}
				idx = jacob.next();
			}
		}
	}
	return (IntWrapper::getCompCount());
}