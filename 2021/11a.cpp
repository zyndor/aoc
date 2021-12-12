#include "utils.h"
#include <iostream>
#include <set>
#include <cassert>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	if (argc < 3)
	{
		std::cerr << "Specify number of steps as 2nd param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	std::vector<uint8_t> octopi;
	octopi.reserve(100);
	ReadAllLines(file, [&octopi](std::string const& str){
		for (auto c: str)
		{
			auto v = c - '0';
			assert(v >= 0 && v < 9);
			octopi.push_back(v);
		}
	});

	auto result = 0ull;
	for (int step = 0, steps = atoi(argv[2]); step < steps; ++step)
	{
		for (auto& o : octopi)
		{
			++o;
		}

		uint32_t flashes = 0;
		std::set<uint32_t> flashed;
		do
		{
			flashes = 0;
			for (auto& o : octopi)
			{
				if (o <= 9)
				{
					continue;
				}

				auto p = &o - octopi.data();
				if (flashed.find(p) != flashed.end())
				{
					continue;
				}

				++flashes;
				flashed.insert(p);

				int x = p % 10;
				int y = p / 10;
				for (auto y0 = y - (y > 0), y1 = y + (y < 9); y0 <= y1; ++y0)
				{
					for (auto x0 = x - (x > 0), x1 = x + (x < 9); x0 <= x1; ++x0)
					{
						auto p1 = y0 * 10 + x0;
						++octopi[p1];
					}
				}
			}
		} while (flashes > 0);

		result += flashed.size();

		for (auto& o : octopi)
		{
			o *= o <= 9;
		}
	}

	std::cout << result << std::endl;

	return 0;
}
