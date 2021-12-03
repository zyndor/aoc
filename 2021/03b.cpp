#include <algorithm>
#include <iostream>
#include <fstream>
#include <bitset>
#include <cstring>
#include <cstdio>
#include <cassert>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	auto result = 0;
	std::ifstream file(argv[1]);
	std::string line;

	std::vector<uint32_t> samples;

	uint32_t digits = 0;
	while (std::getline(file, line))
	{
		digits = std::max<uint32_t>(digits, line.size());

		uint32_t bits = 0;
		uint32_t sample = 0;
		for (auto i = line.rbegin(); i != line.rend(); ++i)
		{
			sample |= (*i == '1') << bits;
			++bits;
		}

		samples.push_back(sample);
	}

	auto oxygen = samples;
	for (auto bits = digits; bits-- > 0 && oxygen.size() > 1;)
	{
		auto bitCount = 0;
		for (auto& s : oxygen)
		{
			bitCount += (s >> bits) & 1;
		}

		auto bit = (bitCount >= ((oxygen.size() + 1) / 2));
		std::cout << "bit " << bits << ": " << bitCount << " / " << oxygen.size() <<
			" -> " << bit << std::endl;

		oxygen.erase(std::remove_if(oxygen.begin(), oxygen.end(), [bits, bit](uint32_t d){
			return ((d >> bits) & 1) != bit;
		}), oxygen.end());
	}

	auto co2 = samples;
	for (auto bits = digits; bits-- > 0 && co2.size() > 1;)
	{
		auto bitCount = 0;
		for (auto& s : co2)
		{
			bitCount += (s >> bits) & 1;
		}

		auto bit = (bitCount < ((co2.size() + 1) / 2));
		std::cout << "bit " << bits << ": " << bitCount << " / " << co2.size() <<
			" -> " << bit << std::endl;

		co2.erase(std::remove_if(co2.begin(), co2.end(), [bits, bit](uint32_t d){
			return ((d >> bits) & 1) != bit;
		}), co2.end());
	}

	std::cout << "o2: " << oxygen[0] << " (" << std::bitset<12>(oxygen[0]) << ")" << std::endl;
	std::cout << "co2: " << co2[0] << " (" << std::bitset<12>(co2[0]) << ")" << std::endl;
	std::cout << oxygen[0] * co2[0] << std::endl;

	return 0;
}
