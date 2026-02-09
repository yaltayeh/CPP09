#pragma once

class Jacobsthal
{
private:
	unsigned int last;	  // J(n-2)
	unsigned int current; // J(n-1)
	unsigned int index;	  // next n to return

public:
	Jacobsthal();
	~Jacobsthal();
	Jacobsthal(const Jacobsthal &other);
	Jacobsthal &operator=(const Jacobsthal &other);

	unsigned int next();
};