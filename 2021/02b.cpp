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

	int x = 0, y= 0, aim = 0;
	while (std::getline(file, line))
	{
		char buffer[16];
		int units;
		if (sscanf(line.c_str(), "%s %d", buffer, &units) != 2)
		{
			std::cerr << "Bad input" << std::endl;
			exit(1);
		}

		if (strcmp(buffer, "forward") == 0)
		{
			x += units;
			y += aim * units;
		}
		else if (strcmp(buffer, "down") == 0)
		{
			aim += units;
		}
		else if (strcmp(buffer, "up") == 0)
		{
			aim -= units;
		}
	}

	std::cout << x * y << std::endl;

	return 0;
}
