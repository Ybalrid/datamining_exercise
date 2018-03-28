#pragma once

#include <cstdint>
#include <vector>

//This regroups functions used in the "k-mode" computation
namespace kmode
{
	typedef std::vector<uint32_t> kernel;
	//Return the dissimilarity between two numbers
	int dissimilarity(uint32_t a, uint32_t b);
}
