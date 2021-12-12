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
	const std::map<char, Entry> matching{
		{')', { '(', 3 }},
		{']', { '[', 57 }},
		{'}', { '{', 1197 }},
		{'>', { '<', 25137 }}
	};

	const std::map<char, uint32_t> completion{
		{ '(', 1 },
		{ '[', 2 },
		{ '{', 3 },
		{ '<', 4 }
	};

	std::vector<uint64_t> results;
	ReadAllLines(file, [&matching, &completion, &results](std::string const& line){
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
						return;
					}
				}
				break;
			}
		}

		uint64_t score = 0;
		while (!stack.empty())
		{
			auto iFind = completion.find(stack.back());
			if (iFind != completion.end())
			{
				score *= 5;
				score += iFind->second;
			}
			stack.pop_back();
		}

		results.push_back(score);
	});

	std::sort(results.begin(), results.end());

	std::cout << results[results.size() / 2] << std::endl;

	return 0;
}
