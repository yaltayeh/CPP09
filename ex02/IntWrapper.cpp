#include "IntWrapper.hpp"

size_t IntWrapper::comp_count = 0;

IntWrapper::IntWrapper()
	: value(0) {}

IntWrapper::IntWrapper(int value)
	: value(value) {}

IntWrapper &IntWrapper::operator=(int newValue)
{
	value = newValue;
	return *this;
}
IntWrapper &IntWrapper::operator=(const IntWrapper &other)
{
	value = other.value;
	return *this;
}

void IntWrapper::resetCompCount()
{
	comp_count = 0;
}

size_t IntWrapper::getCompCount()
{
	return comp_count;
}

IntWrapper::operator int &()
{
	return value;
}
IntWrapper::operator int() const
{
	return value;
}

bool IntWrapper::operator<(const IntWrapper &other) const
{
	comp_count++;
	return value < other.value;
}
bool IntWrapper::operator>(const IntWrapper &other) const
{
	comp_count++;
	return value > other.value;
}
bool IntWrapper::operator==(const IntWrapper &other) const
{
	comp_count++;
	return value == other.value;
}
bool IntWrapper::operator!=(const IntWrapper &other) const
{
	comp_count++;
	return value != other.value;
}
bool IntWrapper::operator<=(const IntWrapper &other) const
{
	comp_count++;
	return value <= other.value;
}
bool IntWrapper::operator>=(const IntWrapper &other) const
{
	comp_count++;
	return value >= other.value;
}

bool IntWrapper::operator<(const int &other) const
{
	comp_count++;
	return value < other;
}

bool IntWrapper::operator>(const int &other) const
{
	comp_count++;
	return value > other;
}

bool IntWrapper::operator==(const int &other) const
{
	comp_count++;
	return value == other;
}

bool IntWrapper::operator!=(const int &other) const
{
	comp_count++;
	return value != other;
}

bool IntWrapper::operator<=(const int &other) const
{
	comp_count++;
	return value <= other;
}

bool IntWrapper::operator>=(const int &other) const
{
	comp_count++;
	return value >= other;
}
