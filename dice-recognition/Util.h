#ifndef DICE_RECOGNITION_UTIL_H
#define DICE_RECOGNITION_UTIL_H

#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Util
{
public:
	static void error(const std::string& message)
	{
		std::cerr << message << "\n";
		throw(std::exception(message.c_str()));
	}

	static std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim))
			elems.push_back(item);

		return elems;
	}


	static std::vector<std::string> split(const std::string &s, char delim)
	{
		std::vector<std::string> elems;
		return split(s, delim, elems);
	}

	static int toInt(const std::string& str)
	{
		char *end;
		long  i;
		errno = 0;
		int base = 0;
		i = strtol(str.c_str(), &end, base);

		if ((errno == ERANGE && i == LONG_MAX) || i > INT_MAX)
			error("toInt() OVERFLOW: " + str);

		if ((errno == ERANGE && i == LONG_MIN) || i < INT_MIN)
			error("toInt() UNDERFLOW: " + str);

		if (str.empty() || *end != '\0')
			error("toInt() INCONVERTABLE: " + str);

		return i;
	}
};

#endif // DICE_RECOGNITION_UTIL_H