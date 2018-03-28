#pragma once

#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

class HexFileLoader
{
	//Temp storage for loading text
	std::vector<std::string> raw_text;
	//Storage for converted the 32bit hex numbers form text to actual usable numbers
	std::vector<uint32_t> raw_numbers;
	//Load text from file "path"
	void load(const std::string& path);
	//Convert text to numbers and erase the text buffer from memory
	void convertLoadedData();

public:
	//Construct a text loader, will load data imediately
	explicit HexFileLoader(const std::string& path);
	//Return size of loaded data
	inline size_t size() { return raw_numbers.size(); }
	//Return data at index "index"
	inline uint32_t operator[](size_t index) { return raw_numbers[index]; }
	//raw pointer to data
	inline uint32_t* data() { return raw_numbers.data(); }

	//Iterator access definition (for use in C++ stl algorithms)
	inline decltype(auto) begin() { return raw_numbers.begin(); }
	inline decltype(auto) end() { return raw_numbers.end(); }
};
