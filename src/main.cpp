#include <iostream>

#include "HexFileLoader.hpp"
#include "KMode.hpp"
#include <ctime>

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
	//srand(42);
	srand(time(nullptr));

	cout << "Datamining\n";
	HexFileLoader total("./jeu_tot");
	HexFileLoader only_bad("./jeu_1");

	std::cout << "dissim= " << kmode::dissimilarity(total[0], total[1]) << '\n';

	//choose two kernels (3 random points)
	kmode::kernel CmpA, CmpB, A, B;
	CmpA.push_back(total[rand() % total.size()]);

	CmpB.push_back(total[rand() % total.size()]);

	//for each poin in the total dataset
	for(auto& point : total)
	{
		//Distance storage
		int distA = 0, distB = 0;

		//Compute distance between each point of A and current point
		for(auto& i : CmpA)
			distA += kmode::dissimilarity(i, point);

		//Same with B
		for(auto& i : CmpB)
			distB += kmode::dissimilarity(i, point);

		//If distA smaller that dist B, add point to A
		if(distA < distB)
			A.push_back(point);
		//If distaB is actually the smaller one, add to B
		else
			B.push_back(point);
	}

	std::cout << "Group A contains : " << A.size() << " points\n";
	std::cout << "Group B contains : " << B.size() << " points\n";

	return pause_before_exit();
}
