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

	const uint32_t max = 1 << 31;
	uint32_t samples[] { max, max, max, max };
	uint32_t result = 0;
	ReadAllLines(file, [&samples, &result](std::string const& line) {
		for (int i = 0; i < 3; ++i)
		{
			samples[i] = samples[i + 1];
		}

		samples[3] = atoi(line.c_str());

		result += samples[3] > samples[0];
	});

	std::cout << result << std::endl;

	return 0;
}
