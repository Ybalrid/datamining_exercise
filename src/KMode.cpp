#include "KMode.hpp"
#include <ios>
#include <iostream>
#include <tuple>
#include <sstream>
#include <iomanip>
#include <algorithm>

int kmode::dissimilarity(uint32_t a, uint32_t b)
{
	int distance = 0;

	//std::cerr << "A = " << std::hex << a << '\n';
	//std::cerr << "B = " << std::hex << b << '\n';

	//Decompose numbers as 4bit digits (hex digit)
	unsigned char a_digits[8], b_digits[8];
	for(size_t i{ 0 }; i < 8; ++i)
	{
		a_digits[i] = (a >> 4 * i) & 0xF;
		b_digits[i] = (b >> 4 * i) & 0xF;
	}

	//Calculate "distance" by comparig A's and B's
	for(size_t i{ 0 }; i < 8; ++i)
	{
		//std::cerr
		//	<< "a digit "
		//	<< std::dec
		//	<< i
		//	<< " "
		//	<< std::hex
		//	<< int(a_digits[i])
		//	<< '\n';

		//std::cerr
		//	<< "b digit "
		//	<< std::dec
		//	<< i
		//	<< " "
		//	<< std::hex
		//	<< int(b_digits[i])
		//	<< '\n';

		if(a_digits[i] != b_digits[i])
			distance++;
	}
	//std::cerr << std::dec;
	return distance;
}

int kmode::levenstein(uint32_t a, uint32_t b)
{
	//Convert to string
	std::stringstream s;
	std::string sa, sb;
	s << std::setw(8) << std::setfill('0') << std::hex << a;
	sa = s.str();
	s.str("");
	s << std::setw(8) << std::setfill('0') << std::hex << b;
	sb = s.str();

	//Levenstein impl
	auto dist = [](const std::string& s1, const std::string& s2) {
		const std::size_t len1 = s1.size(), len2 = s2.size();
		std::vector<std::vector<unsigned int>> d(len1 + 1, std::vector<unsigned int>(len2 + 1));

		d[0][0] = 0;
		for(unsigned int i = 1; i <= len1; ++i) d[i][0] = i;
		for(unsigned int i = 1; i <= len2; ++i) d[0][i] = i;

		for(unsigned int i = 1; i <= len1; ++i)
			for(unsigned int j = 1; j <= len2; ++j)
				d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + (s1[i - 1] == s2[j - 1] ? 0 : 1) });
		return d[len1][len2];
	};

	return dist(sa, sb);
}

uint32_t kmode::mean(const kernel& k)
{
	int64_t acc = 0;

	//Sum up everything, divide by size
	for(auto p : k) acc += p;
	return acc / (int64_t)k.size();
}

std::tuple<uint32_t, uint32_t, uint32_t> kmode::get3SmallestDistance(const kmode::kernel& k, uint32_t number)
{
	//To store the 3 smallest distance numbers, and their associated distance
	uint32_t min[3] = { k[0], k[0], k[0] };
	auto init		= dissimilarity(number, min[0]);
	int minDist[3]  = { init, init, init };
	uint32_t currentPointDistance;
	//For each point on kernel
	for(auto point : k)
	{
		currentPointDistance = kmode::dissimilarity(number, point);
		if(currentPointDistance < minDist[0])
		{
			//shift the 3 distances
			std::rotate(std::rbegin(min), std::rbegin(min) + 1, std::rend(min));
			std::rotate(std::rbegin(minDist), std::rbegin(minDist) + 1, std::rend(minDist));
			//Replace number 0
			min[0]	 = point;
			minDist[0] = currentPointDistance;
		}
	}

	//Retrun 3 numbers with tie()
	return std::tie(min[0], min[1], min[2]);
}
