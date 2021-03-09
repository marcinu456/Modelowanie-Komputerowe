#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	active = false;
	cols = 50;
	rows = 50;

	cellWidth = ofGetWidth() / cols;
	cellHeight = ofGetHeight() / cols;


	clear();
	ofBackground(ofColor::white);
	ofSetFrameRate(60);
}


//--------------------------------------------------------------
void ofApp::update(){
	if (active) {
		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++) {
				
				matrix.arrays[i][j].activeNeighbors = getActiveNeighbors(i, j);
				bool currentCellState = matrix.arrays[i][j].currentState;
				int activeNeighbors = matrix.arrays[i][j].activeNeighbors;

				if (currentCellState == true && activeNeighbors < 2) {
					matrix.arrays[i][j].nextState = false;
				}
				else if (currentCellState == true && activeNeighbors > 3) {
					matrix.arrays[i][j].nextState = false;
				}
				else if (currentCellState == true && activeNeighbors > 1 && activeNeighbors < 4) {
					matrix.arrays[i][j].nextState = true;
					matrix.arrays[i][j].color = ofColor::green;
				}
				else if (currentCellState == false && activeNeighbors == 3) {
					matrix.arrays[i][j].nextState = true;
					matrix.arrays[i][j].color = ofColor::green;
				}
			}
		}
		makeNextStateCurrent();
	}
}


int ofApp::getActiveNeighbors(int column, int row)
{
	int howManyNeighbors = 0;

	int prevCol = column - 1;
	int nextCol = column + 1;
	int prevRow = row - 1;
	int nextRow = row + 1;

	howManyNeighbors += currentCellState(prevCol, prevRow);
	howManyNeighbors += currentCellState(prevCol, row);
	howManyNeighbors += currentCellState(prevCol, nextRow);

	howManyNeighbors += currentCellState(column, prevRow);
	howManyNeighbors += currentCellState(column, nextRow);

	howManyNeighbors += currentCellState(nextCol, prevRow);
	howManyNeighbors += currentCellState(nextCol, row);
	howManyNeighbors += currentCellState(nextCol, nextRow);

	return howManyNeighbors;
}

int ofApp::currentCellState(int column, int row)
{
	if (column >= 0 && row >= 0 &&
		column < cols && row < rows &&
		matrix.arrays[column][row].currentState == true)
	{
		return 1;
	}
	return 0;

}



void ofApp::makeNextStateCurrent()
{
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			matrix.arrays[i][j].currentState = matrix.arrays[i][j].nextState;
		}
	}
}

void ofApp::randomGrid()
{
	clear();
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			if(rand()/(float)RAND_MAX < 0.25)
				matrix.arrays[i][j].currentState = !matrix.arrays[i][j].currentState;
		}
	}

}



//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			ofSetColor(ofColor::black);
			ofNoFill();
			ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
			if (matrix.arrays[i][j].currentState == true) {
				ofSetColor(ofColor::green);
				ofFill();
				ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
				ofNoFill();
			}
		}
	}
}



void ofApp::clear()
{
	std::cout << "clear\n";
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			matrix.arrays[i][j].currentState = false;
			matrix.arrays[i][j].nextState = false;
		}
	}
}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case ' ':
			active = !active;
			break;
		case 'r':
			clear();
			break;
		case 'f':
			randomGrid();
			break;
		default:
			break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	int xcell = x / cellWidth;
	int ycell = y / cellHeight;
	if (xcell < cols && ycell < rows)
	{
		//grid[xcell][ycell].currentState = !grid[xcell][ycell].currentState;
		matrix.arrays[xcell][ycell].currentState = !matrix.arrays[xcell][ycell].currentState;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
