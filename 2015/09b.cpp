#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	std::string line;

	struct Node
	{
		std::map<std::string, uint32_t> distances;
	};
	std::map<std::string, Node> locations;

	while (std::getline(file, line))
	{
		char sourceBuffer[64];
		char targetBuffer[64];
		uint32_t distance;
		if (sscanf(line.c_str(), "%64s to %64s = %u", sourceBuffer, targetBuffer, &distance) != 3)
		{
			std::cout << "Failed to parse '" << line << "'" << std::endl;
			continue;
		}

		locations[sourceBuffer].distances[targetBuffer] = distance;
		locations[targetBuffer].distances[sourceBuffer] = distance;
	}

	uint32_t maxDistance = 0;
	for (auto& s: locations)
	{
		struct Node
		{
			std::string name;
			uint32_t distance;
		};
		std::vector<Node> open;
		std::vector<std::string> closed;
		uint32_t distance = 0;

		open.push_back({ s.first, 0 });
		while (!open.empty())
		{
			const auto current = open.back();
			std::cout << current.name << "(" << current.distance << ") -> ";
			open.pop_back();

			distance += current.distance;

			auto iInsert = std::lower_bound(closed.begin(), closed.end(), current.name);
			closed.insert(iInsert, current.name);

			uint32_t nextDist = 0;
			std::string next;
			for (auto& n: locations.find(current.name)->second.distances)
			{
				if (auto i = std::lower_bound(closed.begin(), closed.end(), n.first);
					i == closed.end() || *i != n.first)
				{
					if (n.second > nextDist)
					{
						next = n.first;
						nextDist = n.second;
					}
				}
			}

			if (!next.empty())
			{
				open.push_back(Node{ next, nextDist });
			}
		}

		std::cout << distance << std::endl;
		if (distance > maxDistance)
		{
			maxDistance = distance;
		}
	}

	std::cout << maxDistance << std::endl;

	return 0;
}
