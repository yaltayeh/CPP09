#pragma once

#include <stack>

class RPN
{
private:
	std::stack<int> _stack;

public:
	RPN();
	~RPN();

	int evaluate(const std::string &expression);

	class RPNException : public std::runtime_error
	{
	private:
		size_t _pos;

	public:
		RPNException(const std::string &message, size_t pos);
		size_t getPosition() const;
	};
};
