#include "../utils.h"
#include <iostream>
#include <map>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::map<uint32_t, uint32_t> lines;
	std::ifstream inFile(argv[1]);
	ReadAllLines(inFile, [&lines](std::string line)
	{
		int x1, y1, x2, y2;
		if (sscanf(line.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) != 4)
		{
			std::cerr << "Failed to parse '" << line << "'" << std::endl;
		}
		else
		{
			int dx = ((x2 - x1) > 0) - ((x2 - x1) < 0);
			int dy = ((y2 - y1) > 0) - ((y2 - y1) < 0);
			x2 += dx;
			y2 += dy;
			if (dx * dx + dy * dy == 1)
			{
				for (; !(x1 == x2 && y1 == y2); x1 += dx, y1 += dy)
				{
					++lines[(y1 << 16) + x1];
				}
			}
		}
	});

	uint32_t result = std::count_if(lines.begin(), lines.end(), [](auto const& x){
		return x.second > 1;
	});
	std::cout << result << std::endl;

	return 0;
}
