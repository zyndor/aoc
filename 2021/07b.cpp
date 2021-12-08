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

	std::vector<uint32_t> crabs;
	ReadAllLines(file, [&crabs](const std::string& line){
		for (auto i = line.begin(), i1 = line.end(); i != i1;)
		{
			crabs.push_back(atoi(&*i));
			i = std::find(i, i1, ',');
			i += i != i1;
		}
	});

	const uint32_t mean = std::accumulate(crabs.begin(), crabs.end(), 0) / crabs.size();

	uint32_t result = Reduce<uint32_t>(crabs, [mean](auto e, auto f) {
		auto inc = f < mean ? mean - f : f - mean;
		return e + (inc * (inc + 1)) / 2;
	});

	std::cout << result << std::endl;

	return 0;
}
