#pragma once
 
#include "cell.h" 
#include "ofMain.h" 
#include "../addons/ofxHistoryPlot/src/ofxHistoryPlot.h"
#include "ofxGui.h"
#include <random>

class Matrix 
{ 
public: 
	 
	int rows; 
	int columns; 
	size_t liveTime = 0;

	float cellWidth, cellHeight;

	Cell** cell;
	 
	Matrix(int rows, int columns);
	void clear();
	void randomGrid(double chanceToLive);
	void update(bool active);
	int getActiveNeighbors(int column, int row);
	int currentCellState(int column, int row);
	void makeNextStateCurrent();
	void writeToFile(size_t currentLiveCell);
	void draw();
	void mousePressed(int x, int y, int button);

	ofxHistoryPlot* plot;

	ofxPanel gui;
	ofxFloatSlider chanceToLiveD;
}; 