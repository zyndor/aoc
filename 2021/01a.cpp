#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	auto result = 0;
	std::ifstream file(argv[1]);
	std::string line;
	uint32_t last = 0;
	while (std::getline(file, line))
	{
		uint32_t sample = atoi(line.c_str());

		result += sample > last;
		last = sample;
	}

	std::cout << result << std::endl;

	return 0;
}
