#pragma once

#include <string>
#include <ostream>

struct Benchmark
{
	const std::string name;
	const size_t comparisons;
	const size_t size;
	const double time;

	Benchmark(const std::string &name, size_t comparisons, size_t size, double time);
	~Benchmark();
	Benchmark(const Benchmark &other);
	Benchmark &operator=(const Benchmark &other);

	void printTime(std::ostream &os) const;
	const std::string &timeUnit() const;
};

std::ostream &operator<<(std::ostream &os, const Benchmark &bm);
