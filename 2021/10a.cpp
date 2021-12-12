#include "utils.h"
#include <iostream>
#include <map>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);

	struct Entry
	{
		char pair;
		uint32_t score;
	};
	const std::map<char, Entry> matching {
		{')', { '(', 3 }},
		{']', { '[', 57 }},
		{'}', { '{', 1197 }},
		{'>', { '<', 25137 }}
	};

	auto result = 0;
	ReadAllLines(file, [&matching, &result](std::string const& line){
		std::vector<char> stack;
		stack.reserve(1024);

		for (auto c: line)
		{
			switch(c)
			{
			case '(':
			case '[':
			case '{':
			case '<':
				stack.push_back(c);
				break;
			default:
				if (auto iFind = matching.find(c); iFind != matching.end())
				{
					if (!stack.empty() && stack.back() == iFind->second.pair)
					{
						stack.pop_back();
					}
					else
					{
						result += iFind->second.score;
						return;
					}
				}
				break;
			}
		}
	});

	std::cout << result << std::endl;

	return 0;
}
