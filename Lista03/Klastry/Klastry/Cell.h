#pragma once
struct Cell {
	bool currentState = false;
	int activeNeighbors = 0;
	int number = 0;
	int posX = 0;
	int posY = 0;
};
