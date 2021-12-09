#include "utils.h"
#include <iostream>
#include <set>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::set<uint32_t> digitLen { 2, 3, 4, 7 };

	uint32_t count = 0;
	std::ifstream file(argv[1]);
	ReadAllLines(file, [digitLen, &count](std::string const& line){
		std::istringstream in(line);
		for (uint32_t i = 0; i < 10; ++i)
		{
			std::string signal;
			in >> signal;
		}

		std::string digit;
		in >> digit;	// |

		for (int i = 0; i < 4; ++i)
		{
			in >> digit;

			auto iFind = digitLen.find(digit.size());
			if (iFind != digitLen.end())
			{
				++count;
			}
		}
	});

	std::cout << count << std::endl;

	return 0;
}
