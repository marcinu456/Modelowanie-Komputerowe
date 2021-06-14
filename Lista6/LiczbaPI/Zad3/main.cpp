#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <chrono>
#include <fstream>
#include <filesystem>
#define _USE_MATH_DEFINES
#include <math.h>


double myFunction(double x)

{
	return (1.0 - x) / x;
}

void monteCasino(double lowBound, double upBound, long long iterations)
{
	std::ofstream ofs_energy;
	ofs_energy.open("calka.txt");
	std::random_device rd{};
	std::mt19937_64 engine{ rd() };
	//std::default_random_engine rd;
	//int seed = std::chrono::system_clock::now().time_since_epoch().count();
	//rd.seed(seed);
	std::uniform_real_distribution<double> dis(0.0, DBL_MAX);
	double totalSum = 0;
	double randNum, functionVal;

	long long iter = 0;

	while (iter < iterations - 1)
	{

		randNum = lowBound + (dis(rd) / DBL_MAX) * (upBound - lowBound);

		functionVal = myFunction(randNum);

		totalSum += functionVal;



		if (iter % 5'000'000 == 0)
		{
			ofs_energy << iter << " " << std::setprecision(12) << (upBound - lowBound) * totalSum / iter << std::endl;
		}
		iter++;
	}

}
int main()
{

	double lowerBound, upperBound;
	long long iterations;

	lowerBound = 1;
	upperBound = 2.3;
	iterations = 5'000'000'000;

	monteCasino(lowerBound, upperBound, iterations);



	return 0;
}


