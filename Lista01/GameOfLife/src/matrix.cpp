#include "matrix.h" 
#include <fstream>

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



	plot = new ofxHistoryPlot(NULL, "Cells", 1000, false); //NULL cos we don't want it to auto-update. confirmed by "true"
	plot->setRange(0, 1200); //hard range, will not adapt to values off-scale
	plot->addHorizontalGuide(ofGetHeight() / 2, ofColor(255, 0, 0)); //add custom reference guides
	plot->setColor(ofColor::black); //color of the plot line
	plot->setShowNumericalInfo(true);  //show the current value and the scale in the plot
	plot->setRespectBorders(true);	   //dont let the plot draw on top of text
	plot->setLineWidth(1);				//plot line width
	plot->setBackgroundColor(ofColor(0, 220)); //custom bg color
	//custom grid setup
	plot->setDrawGrid(true);
	plot->setGridColor(ofColor(30)); //grid lines color
	plot->setGridUnit(14);
	plot->setCropToRect(true);





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
	size_t currentLiveCell = 0;
	liveTime = 0;
	clear();
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			if (rand() / (float)RAND_MAX < 0.6) {
				cell[i][j].currentState = !cell[i][j].currentState;
				currentLiveCell++;
			}
		}
	}
	ofstream myfile;
	myfile.open("example.txt");
//	myfile << liveTime << "	" << currentLiveCell << "\n";
	myfile.close();
}

void Matrix::update(bool active) {
	if (active && liveTime < 1000) {
		size_t currentLiveCell = 0;
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
				}
				else if (currentCellState == false && activeNeighbors == 3) {
					cell[i][j].nextState = true;
				}
				if (currentCellState == true)
				{
					currentLiveCell++;
				}

			}
		}
		writeToFile(currentLiveCell);
		plot->update(currentLiveCell);
		makeNextStateCurrent();
	}
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

void Matrix::writeToFile(size_t currentLiveCell)
{
	liveTime++;
	ofstream myfile;
	myfile.open("example.txt", std::ios::app);;
	myfile << liveTime <<"	" << currentLiveCell <<"\n";
	myfile.close();
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
	plot->draw(1024, 10, 640, 240);
}