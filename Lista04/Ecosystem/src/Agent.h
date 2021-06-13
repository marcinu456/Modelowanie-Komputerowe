#pragma once
#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

enum State : size_t { sucker, coward, beard, impostor };
class Agent
{
public:
	ofVec2f position;
	bool currentStatus = true;
	size_t hp;
	ofxAssimpModelLoader yourModel;
	Agent(ofVec2f position, size_t hp);
	virtual void draw(ofColor color) {};
};

