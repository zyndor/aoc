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
	std::string line;

	std::vector<uint32_t> crabs;
	std::getline(file, line);
	ReadInts<uint32_t>(line, [&crabs](auto c){
		crabs.push_back(c);
	});

	std::sort(crabs.begin(), crabs.end());

	uint32_t median = crabs[crabs.size() / 2];
	if ((crabs.size() & 1) == 0)
	{
		median += crabs[crabs.size() / 2 + 1];
		median /= 2;
	}

	auto result = Reduce<uint32_t>(crabs, [median](auto e, auto f) {
		return e + (f < median ? median - f : f - median);
	});

	std::cout << result << std::endl;

	return 0;
}
