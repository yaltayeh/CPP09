#include <iostream>
#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

int RPN::evaluate(const std::string &expression)
{
	_stack = std::stack<int>();
	size_t pos = 0;
	while (true)
	{
		size_t start = expression.find_first_not_of(" ", pos);
		if (start == std::string::npos)
			break;
		size_t end = expression.find_first_of(" ", start);
		std::string token = expression.substr(start, end - start);
		pos = end;
		if (token.length() != 1)
			throw RPN::RPNException("Invalid token length", start);
		char c = token[0];
		if (c >= '0' && c <= '9')
		{
			_stack.push(c - '0');
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (_stack.size() < 2)
				throw RPN::RPNException("Not enough operands", start);
			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();
			int result;
			switch (c)
			{
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				if (b == 0)
					throw RPN::RPNException("Division by zero", start);
				result = a / b;
				break;
			}
			_stack.push(result);
		}
		else
		{
			throw RPN::RPNException("Invalid character", start);
		}
	}
	if (_stack.size() != 1)
		throw RPN::RPNException("Invalid expression", expression.length());
	return _stack.top();
}

RPN::RPNException::RPNException(const std::string &message, size_t pos)
	: std::runtime_error(message), _pos(pos)
{
}

size_t RPN::RPNException::getPosition() const
{
	return _pos;
}
