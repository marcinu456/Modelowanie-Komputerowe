#include <iostream>

int main()
{
	double a = 0.4340000;
	double b = 0.4340001;
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
		std::cout << b << std::endl;
	}
}