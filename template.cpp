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
	ReadAllLines(file, [](std::string const& str){
	});

	auto result = 0;
	std::cout << result << std::endl;

	return 0;
}
