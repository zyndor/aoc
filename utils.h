#pragma once

#include <functional>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdint>

inline
int32_t CountBits(uint32_t v)
{
        uint32_t n = 0;
        while (v)
        {
                ++n;
                v &= v - 1;
        }
        return n;
}

template <typename T>
uint32_t ReadInts(std::string const& line, std::function<void(T)> fn, char delimiter = ',')
{
	std::istringstream iss;
	T result;
	uint32_t errs = 0;
	for (auto i0 = line.begin(), i1 = line.end(); i0 != i1;)
	{
		iss.clear();

		auto iNext = std::find(i0, i1, delimiter);
		std::string token(i0, iNext);
		iss.str(token);
		if (iss >> result)
		{
			fn(result);
		}
		else
		{
			++errs;
		}

		i0 = iNext + (iNext != i1);
	}
	return errs;
}

inline
void ReadAllLines(std::ifstream& fin, std::function<void(std::string const&)> fn)
{
	std::string line;
	while (std::getline(fin, line))
	{
		fn(line);
	}
}

template <typename T>
T Reduce(std::vector<T> const& in, std::function<T(T, T)> fn, T init = {})
{
	return std::accumulate(in.begin(), in.end(), init, fn);
}

struct UnionFind
{
        explicit UnionFind(uint32_t size):
		mCount{ size },
		mNodes{ size, Node{ 0, 1 } }
        {
                for (auto& n : mNodes)
                {
                        n.parent = &n - mNodes.data();
                }
        }

        void Union(uint32_t x, uint32_t y)
        {
                uint32_t xp = Find(x);
                uint32_t yp = Find(y);
                if (xp != yp)
                {
                        if (mNodes[xp].size <= mNodes[yp].size)
                        {
                                mNodes[xp].parent = yp;
                                mNodes[yp].size += mNodes[xp].size;
                        }
                        else
                        {
                                mNodes[yp].parent = xp;
                                mNodes[xp].size += mNodes[yp].size;
                        }
                        --mCount;
                }
        }

        uint32_t Find(uint32_t x) const
        {
                while (mNodes[x].parent != x)
                {
                        x = mNodes[x].parent;
                }
                return x;
        }

        uint32_t Size(uint32_t x) const
        {
                return mNodes[Find(x)].size;
        }

        uint32_t Count() const
        {
                return mCount;
        }

private:
        struct Node
        {
                uint32_t parent;
                uint32_t size;
        };

        uint32_t mCount;
        std::vector<Node> mNodes;
};
