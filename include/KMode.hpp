#pragma once

#include <cstdint>
#include <vector>
#include <tuple>

//This regroups functions used in the "k-mode" computation
namespace kmode
{
	typedef std::vector<uint32_t> kernel;
	//Return the dissimilarity between two numbers
	int dissimilarity(uint32_t a, uint32_t b);
	int levenstein(uint32_t a, uint32_t b);

	//Calculate the mean value of kernel k
	uint32_t mean(const kernel& k);

	//Get the 3 points that have the smallest distance from number inside k
	std::tuple<uint32_t, uint32_t, uint32_t> get3SmallestDistance(const kmode::kernel& k, uint32_t number);
}
