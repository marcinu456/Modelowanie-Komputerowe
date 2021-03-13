#pragma once
 
#include "cell.h" 
#include "ofMain.h" 
#include "../addons/ofxHistoryPlot/src/ofxHistoryPlot.h"

class Matrix 
{ 
public: 
	 
	int rows; 
	int columns; 
	size_t liveTime = 0;

	float cellWidth, cellHeight;
	int sizeOfCell;

	Cell** cell;
	 
	Matrix(int rows, int columns);
	void clear();
	void randomGrid();
	void update(bool active);
	int getActiveNeighbors(int column, int row);
	int currentCellState(int column, int row);
	void makeNextStateCurrent();
	void writeToFile(size_t currentLiveCell);
	void draw();

	ofxHistoryPlot* plot;
}; 