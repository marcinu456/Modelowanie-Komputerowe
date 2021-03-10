#include "matrix.h" 
 
Matrix::Matrix(int _rows, int _columns):
	rows(_rows), columns(_columns)
{  
	cellWidth = ofGetWidth() / rows;
	cellHeight = ofGetHeight() / columns;

	cell = new Cell* [columns];
	for (int i = 0; i < columns; i++) {
		cell[i] = new Cell[rows];
		for (int j = 0; j < rows; j++) {
			cell[i][j].currentState = false;
			cell[i][j].nextState = false;
		}
	}
}
void Matrix::clear()
{
	std::cout << "clear\n";
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			cell[i][j].currentState = false;
			cell[i][j].nextState = false;
		}
	}
}

void Matrix::randomGrid()
{
	clear();
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			if (rand() / (float)RAND_MAX < 0.25)
				cell[i][j].currentState = !cell[i][j].currentState;
		}
	}
}

void Matrix::update(bool active) {
	if (active) {
		ofSetFrameRate(15);
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {

				cell[i][j].activeNeighbors = getActiveNeighbors(i, j);
				bool currentCellState = cell[i][j].currentState;
				int activeNeighbors = cell[i][j].activeNeighbors;

				if (currentCellState == true && activeNeighbors < 2) {
					cell[i][j].nextState = false;
				}
				else if (currentCellState == true && activeNeighbors > 3) {
					cell[i][j].nextState = false;
				}
				else if (currentCellState == true && activeNeighbors > 1 && activeNeighbors < 4) {
					cell[i][j].nextState = true;
					cell[i][j].color = ofColor::green;
				}
				else if (currentCellState == false && activeNeighbors == 3) {
					cell[i][j].nextState = true;
					cell[i][j].color = ofColor::green;
				}
			}
		}
		makeNextStateCurrent();
	}
	ofSetFrameRate(60);
}


int Matrix::getActiveNeighbors(int column, int row)
{
	int howManyNeighbors = 0;
	size_t r = -1;
	int prevCol = (columns + ((column - 1) % columns)) % columns;
	int nextCol = (columns + ((column + 1) % columns)) % columns;
	int prevRow = (rows + ((row - 1) % rows)) % rows;
	int nextRow = (rows + ((row + 1) % rows)) % rows;

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

int Matrix::currentCellState(int column, int row)
{

	return (column >= 0 && row >= 0 &&
		column < columns && row < rows &&
		cell[column][row].currentState == true);

}



void Matrix::makeNextStateCurrent()
{
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			cell[i][j].currentState = cell[i][j].nextState;
		}
	}
}

void Matrix::draw() {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			ofSetColor(ofColor::black);
			ofNoFill();
			ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
			if (cell[i][j].currentState == true) {
				ofSetColor(ofColor::green);
				ofFill();
				ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
				ofNoFill();
			}
		}
	}
}