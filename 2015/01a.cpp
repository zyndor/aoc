#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	int level = 0;
	std::ifstream file(argv[1]);
	while (file)
	{
		const auto op = file.get();
		switch(op)
		{
		case '(':
			++level;
			break;
		case ')':
			--level;
			break;
		default:
			std::cout << "Illegal character: " << char(op) << " (" << op << ")" << std::endl;
			break;
		}
	}
	std::cout << level << std::endl;
	return 0;
}
