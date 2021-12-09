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

	std::vector<uint8_t> locations;
	locations.reserve(1024*1024);
	uint32_t height = 0;
	uint32_t width = 0;
	ReadAllLines(file, [&width, &height, &locations](std::string const& str){
		++height;
		width = std::max<uint32_t>(width, str.size());

		for (auto& c: str)
		{
			locations.push_back(c - '0');
		}
	});

	uint32_t riskLevel = 0;
	auto i = locations.begin();
	auto y = 0u;
	for (auto iEnd = locations.end(); i != iEnd;)
	{
		auto x = 0u;
		for (auto iRow = i + width; i != iRow; ++i, ++x)
		{
			bool isLow = true;
			if ((x > 0 && *i >= *(i - 1)) ||
				(x + 1 < width && *i >= *(i + 1)) ||
				(y > 0 && *i >= *(i - width)) ||
				(y + 1 < height && *i >= *(i + width)))
			{
				isLow = false;
			}

			riskLevel += isLow * (*i + 1);
		}
		++y;
	}

	std::cout << riskLevel << std::endl;

	return 0;
}
