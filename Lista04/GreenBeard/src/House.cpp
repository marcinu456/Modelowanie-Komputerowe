#include "House.h"

House::House(ofVec2f position, int addres):
	position(position), addres(addres)
{
}

void House::Grow()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> treeDist(1, 2);
	if(householder.size()!=0)
	{
		int countC = 0;
		int countB = 0;
		for (int i = 0; i < householder.size(); i++)
		{
			if (householder[i].state == coward)
			{
				countC++;
			}
			else if (householder[i].state == beard)
			{
				countB++;
			}
		}
		int size = treeDist(rd);
		for (int i = 0; i < size; i++)
		{
			if (countC > countB)
			{
				Agent agent(position, coward);
				householder.push_back(agent);
			}
			else
			{
				Agent agent(position, beard);
				householder.push_back(agent);
			}
		}
	}
}
