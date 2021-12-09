#include "utils.h"
#include <iostream>
#include <map>

uint32_t Hash(std::string const& str)
{
	uint32_t hash = 0;
	for (auto c: str)
	{
		hash |= 1 << (c - 'a');
	}
	return hash;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "Specify filename as 1st param." << std::endl;
		return 1;
	}

	std::map<uint32_t, uint32_t> digitLen {
		{ 2, 1, },
		{ 3, 7, },
		{ 4, 4, },
		{ 7, 8, },
	};

	uint32_t count = 0;
	std::ifstream file(argv[1]);
	ReadAllLines(file, [digitLen, &count](std::string const& line){
		std::istringstream in(line);

		std::map<uint32_t, int32_t> signals;	// hash to value
		std::map<uint32_t, uint32_t> values;
		for (uint32_t i = 0; i < 10; ++i)
		{
			std::string signal;
			in >> signal;

			auto h = Hash(signal);
			auto iFind = digitLen.find(CountBits(h));
			if (iFind != digitLen.end())
			{
				signals[h] = iFind->second;
				values[iFind->second] = h;
			}
			else
			{
				signals[h] = -CountBits(h);
			}
		}

		for (auto& h: signals)
		{
			if (h.second == -5)
			{
				h.second = CountBits(values[7] & h.first) == 3 ? 3 :
					CountBits(values[4] & h.first) == 3 ? 5 : 2;
				values[h.second] = h.first;
			}
		}

		for (auto& h: signals)
		{
			if (h.second == -6)
			{
				h.second = CountBits(values[5] & h.first) == 5 ?
					(CountBits(values[3] & h.first) == 5 ? 9 : 6) : 0;
				values[h.second] = h.first;
			}
		}

		std::string digit;
		in >> digit;	// |

		uint32_t number = 0;
		for (int i = 0; i < 4; ++i)
		{
			number *= 10;
			in >> digit;

			uint32_t hash = Hash(digit);
			auto iFind = signals.find(hash);
			if (iFind == signals.end())
			{
				std::cerr << "Invalid hash" << std::endl;
				exit(1);
			}

			number += iFind->second;
		}

		count += number;
	});

	std::cout << count << std::endl;

	return 0;
}
