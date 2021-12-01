#include <string_view>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

const std::string_view opcodes[]{
	std::string_view("turn on "),
	std::string_view("turn off "),
	std::string_view("toggle ")
};

using Op = void(*)(uint32_t&);
const Op ops[] {
	[](uint32_t& in) { ++in; },
	[](uint32_t& in) { in = in > 0 ? in - 1 : 0; },
	[](uint32_t& in) { in += 2; },
};

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	constexpr uint32_t size = 1000;
	uint32_t lights[size * size];
	std::fill(std::begin(lights), std::end(lights), false);
	std::string line;
	while (std::getline(file, line))
	{
		Op op = nullptr;
		for (auto& o: opcodes)
		{
			if (strncmp(line.c_str(), o.data(), o.size()) == 0)
			{
				op = ops[&o - opcodes];
				line = line.substr(o.size());
				break;
			}
		}

		int x0, y0, x1, y1;
		std::cout << line << " -> ";
		if (sscanf(line.c_str(), "%d,%d through %d,%d", &x0, &y0, &x1, &y1) != 4)
		{
			std::cerr << "Failed to parse " << line << std::endl;
			continue;
		}
		std::cout << x0 << ", " << y0 << ", " << x1 << ", " << y1 << std::endl;

		++x1;
		++y1;

		auto i = lights + (x0 + y0 * size);
		auto dx = x1 - x0;
		while (y0 != y1)
		{
			std::for_each(i, i + dx, op);
			i += size;
			++y0;
		}
	}

	auto result = std::accumulate(std::begin(lights), std::end(lights), 0);
	std::cout << result << std::endl;

	return 0;
}
