#pragma once

#include "ofMain.h"

class Cell {
public:
	bool currentState;
	bool nextState;
	int activeNeighbors;
	ofColor color;
};
