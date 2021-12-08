#include "../utils.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 3 || atoi(argv[2]) == 0)
	{
		std::cerr << "Specify number of days as 2nd param." << std::endl;
		return 1;
	}

	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	std::string line;
	std::getline(file, line);

	std::vector<uint64_t> fish;
	fish.resize(9, 0);
	ReadInts<uint64_t>(line, [&fish](auto f){ ++fish[f]; });

	for (auto day = 0, days = atoi(argv[2]); day < days; ++day)
	{
		auto newf = fish[0];
		for (uint32_t f = 1; f < fish.size(); ++f)
		{
			fish[f - 1] = fish[f];
		}
		fish[8] = newf;
		fish[6] += newf;
	}

	uint64_t total = Reduce<uint64_t>(fish, [](auto a, auto b){ return a + b; });
	std::cout << total << std::endl;

	return 0;
}
