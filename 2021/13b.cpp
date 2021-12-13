#include "utils.h"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	struct Dot
	{
		uint32_t x;
		uint32_t y;

		bool operator==(const Dot& other) const
		{
			return x == other.x && y == other.y;
		}
	};
	std::vector<Dot> dots;
	dots.reserve(1000);

	std::ifstream file(argv[1]);
	ReadAllLines(file, [&dots](std::string const& str){
		Dot d;
		char axis;
		if (sscanf(str.c_str(), "%u,%u", &d.x, &d.y) == 2)
		{
			dots.push_back(d);
		}
		else if(sscanf(str.c_str(), "fold along %c=%u", &axis, &d.x) == 2)
		{
			switch(axis)
			{
			case 'x':
				std::for_each(dots.begin(), dots.end(), [fold=d.x](Dot& d) {
					d.x = d.x - ((d.x > fold) * ((d.x - fold) * 2));
				});
				break;
			case 'y':
				std::for_each(dots.begin(), dots.end(), [fold=d.x](Dot& d) {
					d.y = d.y - ((d.y > fold) * ((d.y - fold) * 2));
				});
				break;
			}
		}
	});

        const Dot max = Reduce<Dot>(dots, [](Dot max, Dot d) {
                return Dot{ std::max(max.x, d.x + 1), std::max(max.y, d.y + 1) };
        }, Dot{ 0, 0 });

	auto hash = [max](Dot const& d){ return d.y * max.x + d.x; };
	std::sort(dots.begin(), dots.end(), [hash](Dot const& a, Dot const& b){
		return hash(a) < hash(b);
	});

	dots.erase(std::unique(dots.begin(), dots.end()), dots.end());

	auto p = dots.begin();
	for (auto y = 0u; y < max.y; ++y)
	{
		for (auto x = 0u; x < max.x; ++x)
		{
			const bool match = (p->x == x && p->y == y);
			std::cout.put(match ? '#' : ' ');
			p += match;
		}
		std::cout << std::endl;
	}

	return 0;
}
