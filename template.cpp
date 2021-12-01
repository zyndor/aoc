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

	auto result = 0;
	std::ifstream file(argv[1]);
	std::string line;
	while (std::getline(file, line))
	{
	}

	std::cout << result << std::endl;

	return 0;
}
