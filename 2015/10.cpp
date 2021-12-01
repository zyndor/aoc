#include <algorithm>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify puzzle string as 1st param." << std::endl;
		return 1;
	}

	uint32_t iterations;
	if (argc < 3 || (iterations = atoi(argv[2])) < 0)
	{
		std::cerr << "Specify iterations as 2nd param." << std::endl;
		return 1;
	}

	std::string result = argv[1];
	for (uint32_t i = 0; i < iterations; ++i)
	{
		std::ostringstream oss;
		char lastChar = result[0];
		uint32_t numReps = 1;
		for (auto j = result.begin() + 1, jEnd = result.end(); j != jEnd; ++j)
		{
			if (*j == lastChar)
			{
				++numReps;
			}
			else
			{
				// todo: multiple digit numbers
				oss << char('0' + numReps) << lastChar;
				lastChar = *j;
				numReps = 1;
			}
		}

		oss << char('0' + numReps) << lastChar;

		result = oss.str();
		//std::cout << result << std::endl;
	}

	std::cout << result.size() << std::endl;

	return 0;
}
