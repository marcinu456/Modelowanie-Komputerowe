#include<iostream>
#include"matrix.h"
int main()
{
	Matrix matrix(500,500);

	for (size_t i = 0; i < 100; i++)
	{
		matrix.randomGrid();
		matrix.update(true, i);
	}
	matrix.writeToFile(0);
	return 0;
}
