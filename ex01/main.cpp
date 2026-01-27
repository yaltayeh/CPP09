#include <iostream>
#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " \"<RPN expression>\"" << std::endl;
		return 1;
	}

	std::string expression = argv[1];
	try
	{
		RPN rpn;
		int result = rpn.evaluate(expression);
		std::cout << result << std::endl;
	}
	catch (const RPN::RPNException &e)
	{
		std::cerr << expression << std::endl;
		size_t pos = e.getPosition();
		pos = (pos > expression.length()) ? expression.length() : pos;
		std::cerr << std::string(pos, ' ') << "^" << std::endl;
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
}