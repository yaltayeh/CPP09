#include "Jacobsthal.hpp"

Jacobsthal::Jacobsthal()
	: last(0), current(1), index(0) {}

Jacobsthal::~Jacobsthal() {}

Jacobsthal::Jacobsthal(const Jacobsthal &other)
	: last(other.last), current(other.current), index(other.index) {}

Jacobsthal &Jacobsthal::operator=(const Jacobsthal &other)
{
	if (this != &other)
	{
		last = other.last;
		current = other.current;
		index = other.index;
	}
	return *this;
}

unsigned int Jacobsthal::next()
{
	if (index < 2)
		return index++; // J(0) = 0, J(1) = 1

	unsigned int next_val = current + 2 * last; // Jn = J(n-1) + 2*J(n-2)
	last = current;
	current = next_val;
	++index;
	return next_val;
}
