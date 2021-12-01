#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

bool hasThreeVowels(const std::string& item)
{
	return  std::count_if(item.begin(), item.end(), [](char c){
		return !!strchr("aeiou", c);
	}) >= 3;
}

bool hasDoubleLetter(const std::string& item)
{
	if (item.size() <= 1)
	{
		return false;
	}

	auto iEnd = item.end() - 1;
	return std::find_if(item.begin(), iEnd, [iEnd](const char& c){
		return c == (&c)[1];
	}) != iEnd;
}

bool hasForbiddenSyllable(const std::string& item)
{
	for (auto& syllable: { "ab", "cd", "pq", "xy" })
	{
		if (strstr(item.c_str(), syllable))
		{
			return true;
		}
	}
	return false;
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
		result += !hasForbiddenSyllable(item) &&
			hasThreeVowels(item) &&
			hasDoubleLetter(item);
	}

	std::cout << result << std::endl;

	return 0;
}
