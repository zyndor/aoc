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

	struct Coord
	{
		int x = 32768;
		int y = 32768;
	};

	auto step = [](char op, Coord& c) {
		switch(op)
		{
		case '<':
			--c.x;
			break;
		case '>':
			++c.x;
			break;
		case 'v':
			--c.y;
			break;
		case '^':
			++c.y;
			break;
		default:
			std::cerr << "invalid op: " << op << " (" << int(op) << ")" << std::endl;
			break;
		}
	};

	std::ifstream file(argv[1]);

	Coord coords[2];
	int i = 0;
	std::set<uint32_t> houses;
	while (file)
	{
		houses.insert(hash(coords[i].x, coords[i].y));

		const auto op = file.get();
		step(op, coords[i]);

		i = (i + 1) & 1;
	}

	std::cout << houses.size() << std::endl;

	return 0;
}
