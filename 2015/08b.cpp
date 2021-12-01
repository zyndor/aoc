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
	uint32_t original = 0;
	uint32_t encoded = 0;
	while (std::getline(file, line))
	{
		original += line.size();
		auto newEncoded = 0;
		for (auto& c: line)
		{
			newEncoded += 1 + (c == '\\' || c == '"');
		}
		newEncoded += 2;
		encoded += newEncoded;

		std::cout << line << " (" << line.size() << " / " << newEncoded << ")" << std::endl;
	}

	std::cout << encoded - original << std::endl;

	return 0;
}
