#include <iostream>

#include "HexFileLoader.hpp"

using std::cin;
using std::cout;

int pause_before_exit()
{
	cout << "Press RETURN to continue...";
	cin.get();
	return EXIT_SUCCESS;
}

int main(void)
{
	cout << "Datamining\n";
	HexFileLoader loader("./jeu_tot");

	//for(size_t i = 0; i < loader.size(); ++i)
	//{
	//	cout << std::hex << loader[i] << '\n';
	//}

	std::cout << "loaded " << loader.size() << " numbers from file\n";

	//for(auto& number : loader)
	//{
	//	cout << "loaded " << number << '\n';
	//}

	return pause_before_exit();
}
