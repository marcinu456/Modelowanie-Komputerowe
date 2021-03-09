#pragma once

#include "ofMain.h"

struct Cell {
	bool currentState;
	bool nextState;
	int activeNeighbors;
	ofColor color;
};
