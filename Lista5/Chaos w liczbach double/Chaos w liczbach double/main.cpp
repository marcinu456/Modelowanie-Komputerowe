#include <iostream>
#include <fstream>
#include <filesystem>
int main()
{
	std::ofstream ofs_a;
	std::ofstream ofs_b;
	ofs_a.open("a.txt");
	ofs_b.open("b.txt");
	double a = 0.50001;
	double b = 0.50002;
	double lambada = 1.999;

	for (size_t i = 0; i < 1000; i++)
	{
		a *= lambada;
		b *= lambada;
		if (a > 1.0)
		{
			a -= 1.0;
		}
		if (b > 1.0)
		{
			b -= 1.0;
		}
		//std::cout << a << std::endl;
		//std::cout << b << std::endl;
		ofs_a << a << std::endl;
		ofs_b << b << std::endl;
		//std::cout << a << std::endl;
		//std::cout << b << std::endl;
	}
}