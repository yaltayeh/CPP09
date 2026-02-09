#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "PmergeMe.hpp"
#include <limits>
#include "Benchmark.hpp"

void printUsage(std::string progName)
{
	std::cerr << "Usage: " << progName << " <list of integers>" << std::endl;
}

IntWrapper parseInt(std::string str)
{
	char *endptr;

	long long num = std::strtoll(str.c_str(), &endptr, 10);
	if (*endptr != '\0')
		throw std::invalid_argument("Invalid integer: \"" + str + "\"");
	if (num < 0)
		throw std::invalid_argument("Negative integer: \"" + str + "\"");
	if (num > std::numeric_limits<int>::max())
		throw std::invalid_argument("Integer overflow: \"" + str + "\"");
	return static_cast<IntWrapper>(num);
}

void printInt(IntWrapper num)
{
	std::cout << num << " ";
}

template <typename T>
void printSequence(const std::string &label, const T &container)
{
	std::cout << label << ": ";
	std::for_each(container.begin(), container.end(), printInt);
	std::cout << std::endl;
}

IntWrapper generateRandomInt()
{
	int ran = rand();
	if (ran < 0)
		ran = -ran;
	return static_cast<IntWrapper>(ran);
}

template <typename T>
Benchmark sort(const std::string &name, T &container)
{
	IntWrapper::resetCompCount();
	clock_t start = clock();
	size_t comp = PmergeMe::sort(container);
	double elapsed = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
	Benchmark bm(name, comp, container.size(), elapsed);
	return bm;
}

int tests(std::vector<IntWrapper> &vec)
{
	try
	{
		printSequence("Original sequence", vec);
		Benchmark bm = sort("std::vector", vec);
		printSequence("Sorted sequence", vec);

		std::cout << bm << std::endl;

		std::deque<IntWrapper> deq(vec.begin(), vec.end());
		bm = sort("std::deque", deq);
		std::cout << bm << std::endl;

		std::list<IntWrapper> lst(vec.begin(), vec.end());
		bm = sort("std::list", lst);
		std::cout << bm << std::endl;
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc == 2 && std::string(argv[1]) == "--help")
	{
		printUsage(argv[0]);
		return 0;
	}

	if (argc > 1 && std::string(argv[1]) == "--rand")
	{
		int numCount = 10000; // default number of random integers
		if (argc > 2)
		{
			try
			{
				numCount = parseInt(argv[2]);
			}
			catch (const std::invalid_argument &e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
				std::cerr << "Usage: " << argv[0] << " --rand [number_of_integers]" << std::endl;
				return 1;
			}
		}
		std::vector<IntWrapper> vec(numCount);
		srand(42); // fixed seed for reproducibility
		std::generate(vec.begin(), vec.end(), generateRandomInt);
		return tests(vec);
		
	}

		if (argc > 1)
		{
			try
			{
				std::vector<IntWrapper> vec(argc - 1);
				std::transform(argv + 1, argv + argc, vec.begin(), parseInt);
				return tests(vec);
			}
			catch (const std::invalid_argument &e)
			{
				std::cerr << "Error: " << e.what() << std::endl;
				std::cerr << "Use --help for usage instructions." << std::endl;
				return 1;
			}
		}
		else
		{
			// tests with random 10000 numbers fallback when no arguments are provided
			std::vector<IntWrapper> vec(10000);
			srand(42); // fixed seed for reproducibility
			std::generate(vec.begin(), vec.end(), generateRandomInt);
			return tests(vec);
		}
		return 0;
	}
