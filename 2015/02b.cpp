#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	uint32_t totalLength = 0;
	std::string str;
	int dim[3];
	while (std::getline(file, str))
	{
		if (sscanf(str.c_str(), "%dx%dx%d", dim, dim + 1, dim + 2) < 3)
		{
			std::cerr << "Failed to parse '" << str << "'" << std::endl;
			continue;
		}

		std::sort(dim, dim + 3);
		auto length = (dim[0] + dim[1]) * 2 + dim[0] * dim[1] * dim[2];
		totalLength += length;
	}

	std::cout << totalLength << std::endl;

	return 0;
}
