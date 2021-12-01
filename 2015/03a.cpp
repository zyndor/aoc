#include <iostream>
#include <fstream>
#include <set>
#include <cstdio>
#include <cassert>

uint32_t hash(int x, int y)
{
	assert(x >= 0 && x <= (1 << 16) - 1);
	assert(y >= 0 && y <= (1 << 16) - 1);
	return (uint16_t(x) << 16) | uint16_t(y);
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	int x = 32768, y = 32768;
	std::set<uint32_t> houses;
	while (file)
	{
		houses.insert(hash(x, y));

		const auto op = file.get();
		switch(op)
		{
		case '<':
			--x;
			break;
		case '>':
			++x;
			break;
		case 'v':
			--y;
			break;
		case '^':
			++y;
			break;
		default:
			std::cerr << "invalid op: " << char(op) << " (" << op << ")" << std::endl;
			break;
		}
	}

	std::cout << houses.size() << std::endl;

	return 0;
}
