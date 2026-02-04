#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "PmergeMe.hpp"
#include <limits>

int parseInt(std::string str)
{
	std::stringstream ss(str);

	long long num;
	ss >> num;
	if (ss.fail() || !ss.eof())
		throw std::invalid_argument("Invalid integer: \"" + str + "\"");
	if (num < 0)
		throw std::invalid_argument("Negative integer: \"" + str + "\"");
	if (num > std::numeric_limits<int>::max())
		throw std::invalid_argument("Integer overflow: \"" + str + "\"");
	return static_cast<int>(num);
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <list of integers>" << std::endl;
		return 1;
	}

	try
	{
		std::vector<int> vec(argc - 1);
		
		std::transform(argv + 1, argv + argc, vec.begin(), parseInt);

		PmergeMe<std::vector<int> > pmergeMe(vec);

		std::cout << std::endl;
	}
	catch (const std::invalid_argument &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
