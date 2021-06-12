#include <iostream>
#include <fstream>
#include <filesystem>
int main()
{
	std::ofstream ofs_energy;
	ofs_energy.open("energy.txt");
	double k = -2;
	for (k; k < 4.0; k += 0.01)
	{
		double x = 0.5;

		for (size_t i = 0; i < 100; i++)
		{
			x = k * x * (1.0 - x);
			if(i>00)
			ofs_energy << k << " " << x << std::endl;
			//std::cout << x << std::endl;
		}
		if (k > 4)
			break;
	}

}