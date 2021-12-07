#pragma once

#include <functional>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>

template <typename T>
uint32_t ReadInts(std::string const& line, std::function<void(T)> fn, char delimiter = ',')
{
	std::istringstream iss;
	T result;
	uint32_t errs = 0;
	for (auto i0 = line.begin(), i1 = line.end(); i0 != i1;)
	{
		iss.clear();

		auto iNext = std::find(i0, i1, delimiter);
		std::string token(i0, iNext);
		iss.str(token);
		if (iss >> result)
		{
			fn(result);
		}
		else
		{
			++errs;
		}

		i0 = iNext + (iNext != i1);
	}
	return errs;
}

void ReadAllLines(std::ifstream& fin, std::function<void(std::string const&)> fn)
{
	std::string line;
	while (std::getline(fin, line))
	{
		fn(line);
	}
}
