#include <iostream>

#include "HexFileLoader.hpp"
#include "KMode.hpp"

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
	HexFileLoader total("./jeu_tot");
	HexFileLoader only_bad("./jeu_1");

	std::cout << "dissim= " << kmode::dissimilarity(total[0], total[1]) << '\n';

	return pause_before_exit();
}
