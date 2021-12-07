#include "utils.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	uint32_t last = 0;
	uint32_t result = 0;
	ReadAllLines(file, [&last, &result](std::string const& line){
		uint32_t sample = atoi(line.c_str());

		result += sample > last;
		last = sample;
	});

	std::cout << result << std::endl;

	return 0;
}
