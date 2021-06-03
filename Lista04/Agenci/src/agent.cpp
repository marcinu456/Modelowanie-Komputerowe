#include "agent.h"

#include <cmath>

Agent::Agent(ofVec2f p, double v, State s) :
	position(p),
	state(s),
	recoveryTime(-1)
{
	double rad = ofRandom(2 * 3.141592);
	velocity.x = std::cos(rad) * v;
	velocity.y = std::sin(rad) * v;
}