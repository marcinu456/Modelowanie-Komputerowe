#include "matrix.h"

Matrix::Matrix()
{
	rows = 50;
	columns = 50;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			arrays[i][j].currentState = false;
		}
	}
}
