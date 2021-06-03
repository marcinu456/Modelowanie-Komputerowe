#pragma once
#include "ofMain.h"
#include "Agent.h"
class House
{
public:
	std::vector<Agent> householder;
	ofVec2f position;
	int addres;
	House(ofVec2f position, int addres);
};

