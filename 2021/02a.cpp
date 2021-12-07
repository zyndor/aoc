#include "utils.h"
#include <iostream>
#include <cstring>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	int x = 0, y= 0;
	ReadAllLines(file, [&x, &y](std::string const& line){
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
		}
		else if (strcmp(buffer, "down") == 0)
		{
			y += units;
		}
		else if (strcmp(buffer, "up") == 0)
		{
			y -= units;
		}
	});

	std::cout << x * y << std::endl;

	return 0;
}
