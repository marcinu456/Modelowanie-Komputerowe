#include "Agent.h"

Agent::Agent(ofVec2f position, size_t hp):
	position(position), hp(hp)
{
	yourModel.loadModel("human.obj", 20);
	
}

