#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	~Particle();
	void Update();
	void Draw();

private:

	ofVec2f location;
	ofVec2f direction;
	ofVec2f directions[4];
	std::deque<ofVec2f> logs;
};