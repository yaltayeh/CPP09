#include "Benchmark.hpp"

Benchmark::Benchmark(const std::string &name, size_t comparisons, size_t size, double time)
	: name(name), comparisons(comparisons), size(size), time(time)
{
}

Benchmark::~Benchmark()
{
}

Benchmark::Benchmark(const Benchmark &other)
	: name(other.name), comparisons(other.comparisons), size(other.size), time(other.time)
{
}

Benchmark &Benchmark::operator=(const Benchmark &other)
{
	if (this != &other)
	{
		const_cast<std::string &>(name) = other.name;
		const_cast<size_t &>(comparisons) = other.comparisons;
		const_cast<size_t &>(size) = other.size;
		const_cast<double &>(time) = other.time;
	}
	return *this;
}

std::ostream &operator<<(std::ostream &os, const Benchmark &bm)
{
	os << bm.name << ": " << bm.comparisons << " comparisons, " << bm.size << " elements, ";
	bm.printTime(os);
	return os;
}
const std::string &Benchmark::timeUnit() const
{
	static const std::string units[] = {"s", "ms", "µs", "ns"};
	if (time >= 1.0)
		return units[0];
	else if (time >= 1e-3)
		return units[1];
	else if (time >= 1e-6)
		return units[2];
	else
		return units[3];
}
void Benchmark::printTime(std::ostream &os) const
{
	double displayTime = time;
	if (time >= 1.0)
		displayTime = time;
	else if (time >= 1e-3)
		displayTime = time * static_cast<double>(1e3);
	else if (time >= 1e-6)
		displayTime = time * static_cast<double>(1e6);
	else
		displayTime = time * static_cast<double>(1e9);
	os << displayTime << " " << timeUnit();
}
