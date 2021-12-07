#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
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

	auto countBits = [](uint32_t bits, std::vector<uint32_t>& samples){
		return std::accumulate(samples.begin(), samples.end(), 0ul, [bits](auto s, auto t){
			return s + ((t >> bits) & 1);
		});
	};

	auto filter = [](uint32_t bits, uint32_t bit, std::vector<uint32_t>& samples){
		samples.erase(std::remove_if(samples.begin(), samples.end(), [bits, bit](auto s){
			return ((s >> bits) & 1) != bit;
		}), samples.end());
	};

	auto o2 = samples;
	for (auto bits = digits; bits-- > 0 && o2.size() > 1;)
	{
		size_t bitCount{ countBits(bits, o2) };
		auto bit{ bitCount >= ((o2.size() + 1) / 2) };
		filter(bits, bit, o2);
	}

	auto co2 = samples;
	for (auto bits = digits; bits-- > 0 && co2.size() > 1;)
	{
		size_t bitCount{ countBits(bits, co2) };
		auto bit{ bitCount < ((co2.size() + 1) / 2) };
		filter(bits, bit, co2);
	}

	std::cout << o2[0] * co2[0] << std::endl;

	return 0;
}
