#pragma once

#include <cstddef>

class IntWrapper
{
private:
	int value;
	static size_t comp_count;

public:
	IntWrapper();
	IntWrapper(int value);

	IntWrapper &operator=(int newValue);
	IntWrapper &operator=(const IntWrapper &other);

	static void resetCompCount();

	static size_t getCompCount();

	operator int &();
	operator int() const;

	bool operator<(const IntWrapper &other) const;
	bool operator>(const IntWrapper &other) const;
	bool operator==(const IntWrapper &other) const;
	bool operator!=(const IntWrapper &other) const;
	bool operator<=(const IntWrapper &other) const;
	bool operator>=(const IntWrapper &other) const;

	bool operator<(const int &other) const;
	bool operator>(const int &other) const;
	bool operator==(const int &other) const;
	bool operator!=(const int &other) const;
	bool operator<=(const int &other) const;
	bool operator>=(const int &other) const;
};
