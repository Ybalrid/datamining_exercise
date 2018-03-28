#include "HexFileLoader.hpp"
#include <iostream>

void HexFileLoader::load(const std::string& path)
{
	std::ifstream input(path);
	std::string buffer;
	while(input)
	{
		input >> buffer;
		raw_text.push_back(buffer);
	}
}

void HexFileLoader::convertLoadedData()
{
	for(const auto& str : raw_text)
		raw_numbers.push_back(strtoul(str.c_str(), nullptr, 16));

	raw_text.clear();
}

HexFileLoader::HexFileLoader(const std::string& path)
{
	load(path);
	convertLoadedData();
}
