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

	std::ifstream file(argv[1]);
	auto result = 0;
	std::string line;
	uint32_t samples[4] {};
	uint32_t readings = 0;
	while (std::getline(file, line))
	{
		samples[readings] = atoi(line.c_str());

		for (auto s: samples)
		{
			std::cout << s << "\t";
		}
		std::cout << std::endl;

		result += (samples[1] + samples[2] + samples[3]) >
			(samples[0] + samples[1] + samples[2]);

		if (readings == 3)
		{
			std::copy(samples + 1, samples + 4, samples); 
		}
		readings += readings < 3;
	}

	std::cout << result << std::endl;

	return 0;
}
