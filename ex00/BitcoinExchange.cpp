#include <iostream>
#include <fstream>
#include <sstream>
#include "BitcoinExchange.hpp"

bool parseInt(const std::string &s, int &out)
{
	std::istringstream iss(s);
	iss >> out;
	return !iss.fail() && iss.eof();
}

bool parseDouble(const std::string &s, double &out)
{
	std::istringstream iss(s);
	iss >> out;
	return !iss.fail() && iss.eof();
}

long BitcoinExchange::parseDate(const std::string &str)
{
	long dateValue = 0;

	// Simple date parsing logic (YYYY-MM-DD)
	if (str.length() != 10 || str[4] != '-' || str[7] != '-')
		throw std::invalid_argument("Invalid date format");

	int year;
	int month;
	int day;
	if (!parseInt(str.substr(0, 4), year) ||
		!parseInt(str.substr(5, 2), month) ||
		!parseInt(str.substr(8, 2), day))
		throw std::invalid_argument("Invalid date format");

	if (year < 2009) // Bitcoin started in 2009
		throw std::invalid_argument("Year cannot be before 2009");
	else if (month < 1 || month > 12 || day < 1 || day > 31) // Basic validation
		throw std::invalid_argument("Invalid date values");
	else if (month == 2 && day > 29) // February check
		throw std::invalid_argument("Invalid day for February");
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) // 30-day months check
		throw std::invalid_argument("Invalid day for the month");
	else if (year % 4 != 0 && month == 2 && day == 29) // Leap year check
		throw std::invalid_argument("Invalid day for February in a non-leap year");
	else if (year % 100 == 0 && year % 400 != 0 && month == 2 && day == 29) // Century leap year check
		throw std::invalid_argument("Invalid day for February in a non-leap century year");

	dateValue = year * 10000 + month * 100 + day;

	return dateValue;
}

BitcoinExchange::BitcoinExchange()
{
	loadDataBase(DATABASE_FILE);
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::loadDataBase(const char *filePath)
{
	std::ifstream dbFile(filePath);
	if (!dbFile.is_open())
	{
		throw std::runtime_error("Could not open database file");
	}
	std::string line;
	std::getline(dbFile, line); // Skip header line
	while (std::getline(dbFile, line))
	{
		size_t delimiterPos = line.find(',');
		if (delimiterPos == std::string::npos)
		{
			std::cerr << "Warning: bad data in database => " << line << std::endl;
			continue;
		}
		std::string dateStr = line.substr(0, delimiterPos);
		std::string valueStr = line.substr(delimiterPos + 1);
		try
		{
			long date = parseDate(dateStr);
			double value;
			if (!parseDouble(valueStr, value))
				throw std::invalid_argument("invalid value in database.");
			if (value < 0)
				throw std::invalid_argument("negative value in database.");
			if (dataBase.find(date) != dataBase.end()) // Only insert if date is not already present
				throw std::invalid_argument("duplicate date in database.");
			dataBase[date] = value;
		}
		catch (const std::invalid_argument &e)
		{
			std::cerr << "Warning: bad data in database => " << line << " " << e.what() << std::endl;
			continue;
		}
	}
	dbFile.close();
}

void BitcoinExchange::processFile(const char *filePath)
{
	std::ifstream inFile(filePath);
	if (!inFile.is_open())
	{
		throw std::runtime_error("Could not open input file");
	}

	std::string line;
	std::getline(inFile, line);
	while (std::getline(inFile, line))
	{
		if (line.empty())
			continue;
		size_t delimiterPos = line.find('|');
		if (delimiterPos == std::string::npos)
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string dateStr = line.substr(0, delimiterPos - 1);
		std::string valueStr = line.substr(delimiterPos + 1);

		try
		{
			long date;
			date = parseDate(dateStr);

			// Validate and parse value
			double value;
			if (!parseDouble(valueStr, value))
				throw std::invalid_argument("not a valid number.");
			if (value < 0)
				throw std::invalid_argument("not a positive number.");
			else if (value > 1000)
				throw std::invalid_argument("too large a number.");

			// Find the closest date not greater than the input date
			std::map<long, double>::iterator it = dataBase.lower_bound(date);
			if (it == dataBase.end() || it->first != date)
			{
				if (it == dataBase.begin())
					throw std::invalid_argument("no data available for this date.");
				--it;
			}
			double bitcoinValue = it->second;
			double result = bitcoinValue * value;
			std::cout << dateStr << " => " << value << " = " << result << std::endl;
		}
		catch (const std::invalid_argument &e)
		{
			std::cerr << "Error: bad Date => " << line << " " << e.what() << std::endl;
			continue;
		}
	}
	inFile.close();
}
