#pragma once
#include "ofMain.h"
#include "Agent.h"
#include <random>
class Tree
{
public:
	double deathChance = 0.5;
	bool bPredtaros=false;
	ofVec2f position;
	std::vector<Agent*> agents;
	Tree(bool bPredtaros, ofVec2f position);
	void Eat();
};

