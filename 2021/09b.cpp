#include "utils.h"
#include <iostream>
#include <map>
#include <set>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	std::vector<uint8_t> locations;
	locations.reserve(1024 * 1024);
	uint32_t height = 0;
	uint32_t width = 0;
	ReadAllLines(file, [&width, &height, &locations](std::string const& str) {
		++height;
		width = std::max<uint32_t>(width, str.size());

		for (auto& c: str)
		{
			locations.push_back(c - '0');
		}
	});

	UnionFind uf(locations.size());

	std::set<uint32_t> closed;
	std::vector<uint32_t> open;
	open.reserve(locations.size() / 4);
	constexpr uint32_t kLimit = 9;
	for (auto i = 0u; i < locations.size(); ++i)
	{
		if (closed.find(i) != closed.end())
		{
			continue;
		}

		open.resize(1, i);
		while (!open.empty())
		{
			const auto j = open.back();
			open.pop_back();

			closed.insert(j);
			if (locations[j] >= kLimit)
			{
				continue;
			}

			const auto x = j % width;
			const auto y = j / width;
			if (auto left = j - 1; x > 0 && locations[left] < kLimit)
			{
				open.push_back(left);
				uf.Union(j, left);
			}

			if (auto down = j - width; y > 0 && locations[down] < kLimit)
			{
				open.push_back(down);
				uf.Union(j, down);
			}
		}
	}

	std::set<uint32_t> basins;
	uint32_t max[3]{ 1, 1, 1 };
	for (auto i = 0u; i < locations.size(); ++i)
	{
		auto p = uf.Find(i);
		if (basins.find(p) != basins.end())
		{
			continue;
		}

		auto size = uf.Size(p);
		auto iInsert = std::upper_bound(std::begin(max), std::end(max), size);
		if (iInsert != std::begin(max))
		{
			std::move(max + 1, iInsert, max);
			--iInsert;
			*iInsert = size;
		}

		basins.insert(p);
	}

	auto result = max[0] * max[1] * max[2];
	std::cout << result << std::endl;

	return 0;
}
