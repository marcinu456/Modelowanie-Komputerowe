#include "matrix.h" 
 
Matrix::Matrix(int _rows, int _columns):
	rows(_rows), columns(_columns)
{  
	cellWidth = ofGetWidth() / rows;
	cellHeight = ofGetHeight() / columns;

	arrays = new Cell* [columns];
	for (int i = 0; i < columns; i++) {
		arrays[i] = new Cell[rows];
		for (int j = 0; j < rows; j++) {
			arrays[i][j].currentState = false;
			arrays[i][j].nextState = false;
		}
	}
}
void Matrix::clear()
{
	std::cout << "clear\n";
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			arrays[i][j].currentState = false;
			arrays[i][j].nextState = false;
		}
	}
}

void Matrix::randomGrid()
{
	clear();
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			if (rand() / (float)RAND_MAX < 0.25)
				arrays[i][j].currentState = !arrays[i][j].currentState;
		}
	}
}

void Matrix::update(bool active) {
	if (active) {
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {

				arrays[i][j].activeNeighbors = getActiveNeighbors(i, j);
				bool currentCellState = arrays[i][j].currentState;
				int activeNeighbors = arrays[i][j].activeNeighbors;

				if (currentCellState == true && activeNeighbors < 2) {
					arrays[i][j].nextState = false;
				}
				else if (currentCellState == true && activeNeighbors > 3) {
					arrays[i][j].nextState = false;
				}
				else if (currentCellState == true && activeNeighbors > 1 && activeNeighbors < 4) {
					arrays[i][j].nextState = true;
					arrays[i][j].color = ofColor::green;
				}
				else if (currentCellState == false && activeNeighbors == 3) {
					arrays[i][j].nextState = true;
					arrays[i][j].color = ofColor::green;
				}
			}
		}
		makeNextStateCurrent();
	}
}


int Matrix::getActiveNeighbors(int column, int row)
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

int Matrix::currentCellState(int column, int row)
{
	if (column >= 0 && row >= 0 &&
		column < columns && row < rows &&
		arrays[column][row].currentState == true)
	{
		return 1;
	}
	return 0;

}



void Matrix::makeNextStateCurrent()
{
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			arrays[i][j].currentState = arrays[i][j].nextState;
		}
	}
}

void Matrix::draw() {
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			ofSetColor(ofColor::black);
			ofNoFill();
			ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
			if (arrays[i][j].currentState == true) {
				ofSetColor(ofColor::green);
				ofFill();
				ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
				ofNoFill();
			}
		}
	}
}