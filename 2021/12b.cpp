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

	std::map<std::string, std::set<std::string>> paths;
	ReadAllLines(file, [&paths](std::string const& str){
		auto iDash = str.find('-');
                std::string in = str.substr(0, iDash);
                std::string out = str.substr(iDash + 1);
		paths[in].insert(out);
		paths[out].insert(in);
	});

	struct Frame
	{
		uint32_t dupe;
		std::vector<std::string> visited;
		const decltype(paths)::value_type* options;
		decltype(decltype(paths)::value_type::second)::iterator i;
	};

	auto result = 0;

	std::vector<Frame> stack;
	stack.push_back(Frame{ 0, { "start" }, &*paths.find("start") });
	stack.back().i = stack.back().options->second.begin();
	while (!stack.empty())
	{
		auto& last = stack.back();
		if (last.i == last.options->second.end())
		{
			stack.pop_back();
			continue;
		}

		std::string loc = *last.i;
		++last.i;

		if(loc == "end")
		{
			++result;
			continue;
		}

		if (loc == "start")
		{
			continue;
		}

		Frame next{ last.dupe, last.visited, &*paths.find(loc) };
		if (!isupper(loc[0]))
		{
			auto found = std::find(last.visited.begin(), last.visited.end(), loc) != last.visited.end();
			if (last.dupe > 0 && found)
			{
				continue;
			}

			next.dupe += found;

			next.visited.push_back(loc);
		}

		next.i = next.options->second.begin();
		stack.push_back(next);
	}

	std::cout << result << std::endl;

	return 0;
}
