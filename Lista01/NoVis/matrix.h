#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <vector>
struct Cell {
	bool currentState;
	bool nextState;
	int activeNeighbors;
};

class Matrix
{


	int rows;
	int columns;
	size_t liveTime = 0;
	size_t howMany = 0;

	float cellWidth, cellHeight;
	size_t timeIndex = 1000;

	Cell** cell;
	std::vector<std::vector<size_t>> liveCellVector;

public:
	Matrix(int rows, int columns);
	void clear();
	void randomGrid();
	void update(bool active, size_t index);
	int getActiveNeighbors(int column, int row);
	int currentCellState(int column, int row);
	void makeNextStateCurrent();
	void writeToFile(size_t currentLiveCell);

};
