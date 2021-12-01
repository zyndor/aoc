#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

bool hasLetterPairRepeating(std::string const& item)
{
	if (item.size() < 4)
	{
		return false;
	}

	// thisisastring - 13 letters
	// 0123456789012
	//           ^
	for (auto iBegin = item.begin(), iEnd = item.end() - 3; iBegin != iEnd; ++iBegin)
	{
		auto iEnd2 = iEnd + 2;
		if (std::find_if(iBegin + 2, iEnd2, [iBegin](char const& c){
			bool ok = *iBegin == c &&
				*(iBegin + 1) == (&c)[1];
			if (ok) { std::cout << *iBegin << *(iBegin + 1) << '\t'; }
			return ok;
		}) != iEnd2)
		{
			return true;
		}
	}
	return false;
}

bool hasLetterFlankedByIdenticals(std::string const& item)
{
	if (item.size() < 3) // shouldn't matter, we've already checked for 4.
	{
		return false;
	}

	// thisisastring - 13 letters
	// 0123456789012
	//            ^
	const auto iEnd = item.end() - 2;
	return std::find_if(item.begin(), iEnd, [](char const& c){
		bool ok = c == (&c)[2];
		if (ok) { std::cout << c << (&c)[1] << (&c)[2] << '\t'; }
		return ok;
	}) != iEnd;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::ifstream file(argv[1]);
	auto result = 0;
	std::string item;
	while (std::getline(file, item))
	{
		bool ok = hasLetterPairRepeating(item) &&
			hasLetterFlankedByIdenticals(item);
		if (ok)
		{
			std::cout << item << std::endl;
			++result;
		}
	}

	std::cout << result << std::endl;

	return 0;
}

