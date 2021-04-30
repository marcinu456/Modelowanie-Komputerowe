#pragma once

#include "ofMain.h"

struct Cell {
	bool lastState;
	bool currentState;
	bool nextState;
	int activeNeighbors;
};
