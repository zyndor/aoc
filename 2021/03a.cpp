#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cassert>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	std::string line;

	std::vector<uint32_t> digits;

	uint32_t count = 0;
	while (std::getline(file, line))
	{
		digits.resize(std::max(line.size(), digits.size()));

		uint32_t bits = 0;
		for (auto i = line.rbegin(); i != line.rend(); ++i)
		{
			digits[bits] += (*i == '1');
			++bits;
		}

		++count;
	}

	count = (count + 1) / 2;
	uint32_t gamma = 0;
	uint32_t epsilon = 0;
	uint32_t bits = 0;
	for (auto d = digits.begin(); d != digits.end(); ++d)
	{
		gamma |= (*d > count) << bits;
		epsilon |= (*d < count) << bits;
		++bits;
	}
	std::cout << std::endl;

	std::cout << gamma << ", " << epsilon << std::endl;
	std::cout << uint64_t(gamma) * uint64_t(epsilon) << std::endl;

	return 0;
}
