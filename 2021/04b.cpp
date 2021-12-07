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
	std::string line;
	std::getline(file, line);

	std::vector<uint32_t> drawn;
	ReadInts<uint32_t>(line, [&drawn](auto n){
		drawn.push_back(n);
	});

	struct Ticket
	{
		int32_t data[25];

		void Read(std::ifstream& fin)
		{
			auto n = data;
			std::string line;
			for (int i = 0; i < 5; ++i)
			{
				std::getline(fin, line);
				sscanf(line.c_str(), "%d %d %d %d %d", n, n + 1, n + 2, n + 3, n + 4);
				n += 5;
			}
		}

		bool Mark(int32_t number)
		{
			auto iFind = std::find(std::begin(data), std::end(data), number);
			if (iFind != std::end(data))
			{
				*iFind = -1;

				// check horizontally
				const uint32_t c = std::distance(data, iFind);
				const uint32_t x = c % 5;
				const uint32_t y = c / 5;
				uint32_t hits = 0;
				for (int i = 0; i < 5; ++i)
				{
					hits += data[y * 5 + i] == -1;
				}

				if (hits == 5)
				{
					return true;
				}

				// check vertically
				hits = 0;
				for (int i = 0; i < 5; ++i)
				{
					hits += data[x + 5 * i] == -1;
				}

				if (hits == 5)
				{
					return true;
				}
			}
			return false;
		}

		uint32_t CalculateScore(uint32_t x) const
		{
			uint32_t score = 0;
			for (auto n: data)
			{
				score += n * (n >= 0);
			}
			return score * x;
		}
	};

	std::vector<Ticket> tickets;
	while (std::getline(file, line))
	{
		Ticket t;
		t.Read(file);

		tickets.push_back(t);
	}

	bool done = false;
	auto result = 0;
	for (auto n: drawn)
	{
		for (auto i = tickets.begin(); i != tickets.end();)
		{
			if (i->Mark(n))
			{
				result = i->CalculateScore(n);
				done = tickets.size() == 1;

				i = tickets.erase(i);
			}
			else
			{
				++i;
			}
		}

		if (done) break;
	}

	std::cout << result << std::endl;

	return 0;
}
