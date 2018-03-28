#include "KMode.hpp"
#include <ios>
#include <iostream>

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
