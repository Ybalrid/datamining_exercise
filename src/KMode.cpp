#include "KMode.hpp"
#include <ios>
#include <iostream>
#include <tuple>

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

uint32_t kmode::mean(const kernel& k)
{
	int64_t acc = 0;
	for(auto p : k) acc += p;
	return acc / (int64_t)k.size();
}

std::tuple<uint32_t, uint32_t, uint32_t> kmode::get3SmallestDistance(const kmode::kernel& k, uint32_t number)
{
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
			min[0]	 = point;
			minDist[0] = currentPointDistance;
		}
	}

	return std::tie(min[0], min[1], min[2]);
}
