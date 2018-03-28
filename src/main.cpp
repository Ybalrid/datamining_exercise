#include <iostream>

#include "HexFileLoader.hpp"
#include "KMode.hpp"
#include <ctime>
#include <unordered_map>

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

	//Attempt at implementing kmod
	//choose two first comparaison at random kernels (3 random points)
	kmode::kernel CmpA, CmpB, A, B;
	CmpA.push_back(total[rand() % total.size()]);
	CmpA.push_back(total[rand() % total.size()]);
	CmpA.push_back(total[rand() % total.size()]);

	CmpB.push_back(total[rand() % total.size()]);
	CmpB.push_back(total[rand() % total.size()]);
	CmpB.push_back(total[rand() % total.size()]);

	int lastObj = 0;
	do
	{
		//Will contains the sum of all smallest distances with the current CmpA/B kernels
		int objectif = 0;

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
			{
				A.push_back(point);
				objectif += distA;
			}
			//If distaB is actually the smaller one, add to B
			else
			{
				B.push_back(point);
				objectif += distB;
			}
		}

		std::cout << "objectif = " << std::dec << objectif << '\n';

		std::cout << "Group A contains : " << std::dec << A.size() << " points\n";
		std::cout << "Group B contains : " << std::dec << B.size() << " points\n";

		//Compute mean of A and B
		auto Amean = kmode::mean(A);
		auto Bmean = kmode::mean(B);

		std::cout << "A mean value " << std::hex << Amean << '\n';
		std::cout << "B mean value " << std::hex << Bmean << '\n';

		auto A3smallestDist = kmode::get3SmallestDistance(A, Amean);
		auto B3smallestDist = kmode::get3SmallestDistance(B, Bmean);

		CmpA[0] = std::get<0>(A3smallestDist);
		CmpA[1] = std::get<1>(A3smallestDist);
		CmpA[2] = std::get<2>(A3smallestDist);

		CmpB[0] = std::get<0>(B3smallestDist);
		CmpB[1] = std::get<1>(B3smallestDist);
		CmpB[2] = std::get<2>(B3smallestDist);

		lastObj = objectif;

		//Ditch current partition
		A.clear();
		B.clear();

	} while(1);

	return pause_before_exit();
}
