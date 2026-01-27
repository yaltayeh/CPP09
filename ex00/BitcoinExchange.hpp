#pragma once

#define DATABASE_FILE "data.csv"

#include <map>
#include <string>

class BitcoinExchange
{
private:
	void loadDataBase(const char *filePath);
	long parseDate(const std::string &str);

	std::map<long, double> dataBase;

public:
	BitcoinExchange();
	~BitcoinExchange();
	
	void processFile(const char *filePath);
};
