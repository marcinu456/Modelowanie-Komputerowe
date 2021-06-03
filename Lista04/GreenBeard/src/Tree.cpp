#include "Tree.h"


Tree::Tree(bool bPredtaros, ofVec2f position):
	bPredtaros(bPredtaros),
	position(position)
{}

void Tree::Eat()
{
	if (bPredtaros)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> agentDist(0, 1);
		
		if (agents.size() == 2)
		{
			auto agentNB = agentDist(rd);
			Agent& agent = *agents[agentNB];
			if (agent.state == beard)
			{
				std::uniform_real_distribution<double> dis(0.0, 1.0);
				if (dis(rd) < deathChance)
				{
					agent.currentStatus = false;
				}
			}
			else if (agent.state == coward)
			{
				if (agentNB == 0)
				{
					agents[1]->currentStatus = false;
				}
				else
				{
					agents[0]->currentStatus = false;
				}
			}
		}
		else if (agents.size() == 1)
		{
			Agent& agent = *agents[0];
			std::uniform_real_distribution<double> dis(0.0, 1.0);
			if (dis(rd) < deathChance)
			{
				agent.currentStatus = false;
			}
		}

	}
}
