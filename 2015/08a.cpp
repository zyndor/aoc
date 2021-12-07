#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cassert>

bool ishexa(char c)
{
	return isdigit(c) || (c >= 'a' && c <= 'f');
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	std::string line;
	uint32_t useful = 0;
	uint32_t total = 0;
	while (std::getline(file, line))
	{
		//std::cout << "original: '" << line << "'" << std::endl;

		auto firstQuote = strcspn(line.c_str(), " \t\"");
		assert(firstQuote < line.size());
		auto lastQuote = strrchr(line.c_str(), '\"') - (line.c_str() + firstQuote);
		assert(lastQuote > 0);

		line = line.substr(firstQuote + 1, lastQuote - 1);

		total += line.size() + 2;

		int32_t add = 0;
		bool skip = false;
		for (auto& c : line)
		{
			auto n = size_t(&c - line.c_str());
			if (c == '\\' && n + 1 < line.size() && [&skip]{
				bool tmp = !skip;
				skip = false;
				return tmp;
			}())
			{
				auto c2 = (&c)[1];
				switch (c2)
				{
				case 'x':
					if (n + 3 >= line.size() ||
						!(ishexa((&c)[2]) && ishexa((&c)[3])))
					{
						break;
					}
					add -= 2;
					continue;

				case '"':
					continue;

				case '\\':
					skip = true;
					continue;
				}
			}
			++add;
		}
		assert(add >= 0);
		useful += uint32_t(add);

		std::cout << "stripped: '" << line << "' (" << line.size() + 2 << " / " << add << ")" << std::endl;
	}

	std::cout << total - useful << std::endl;

	return 0;
}
