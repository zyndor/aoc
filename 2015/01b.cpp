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
	int pos = 1;
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

		if (level < 0)
		{
			break;
		}
		++pos;
	}
	std::cout << pos << std::endl;
	return 0;
}
