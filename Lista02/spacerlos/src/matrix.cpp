#include "matrix.h" 
#include <fstream>

Matrix::Matrix(int _rows, int _columns):
	rows(_rows), columns(_columns)
{  
	cellWidth = ofGetWidth() / rows;
	cellHeight = ofGetWidth() / columns;

	cell = new Cell* [columns];
	for (int i = 0; i < columns; i++) {
		cell[i] = new Cell[rows];
		for (int j = 0; j < rows; j++) {
			cell[i][j].currentState = false;
			cell[i][j].nextState = false;
		}
	}

	plot = new ofxHistoryPlot(NULL, "Cells", 1000, false); //NULL cos we don't want it to auto-update. confirmed by "true"
	plot->setRange(0, 1); //hard range, will not adapt to values off-scale
	//plot->addHorizontalGuide(ofGetHeight() / 2, ofColor(255, 0, 0)); //add custom reference guides
	plot->setColor(ofColor::black); //color of the plot line
	plot->setShowNumericalInfo(true);  //show the current value and the scale in the plot
	plot->setRespectBorders(true);	   //dont let the plot draw on top of text
	plot->setLineWidth(1);				//plot line width
	plot->setBackgroundColor(ofColor(220, 220)); //custom bg color
	//custom grid setup
	plot->setDrawGrid(true);
	plot->setGridColor(ofColor(225)); //grid lines color
	plot->setGridUnit(100);
	plot->setCropToRect(true);



	gui.setup();
	gui.add(chanceToLiveD.setup("P", 0.5, 0, 1));

}
void Matrix::clear()
{
	plot->reset();
	std::cout << "clear\n";
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			cell[i][j].currentState = false;
			cell[i][j].nextState = false;
		}
	}
	liveTime = 0;
}

void Matrix::randomGrid(double chanceToLive)
{
	std::random_device rd{};
	std::mt19937 engine{ rd() };
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	size_t currentLiveCell = 0;

	clear();
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			if (dis(rd) < chanceToLiveD) {
				cell[i][j].currentState = !cell[i][j].currentState;
				currentLiveCell++;
			}
		}
	}
	/*ofstream myfile;
	myfile.open("example.txt");
	myfile.close();*/

}

void Matrix::update(bool active) {
	ofSetFrameRate(15);
	if (active && liveTime < 1000) {
		
		size_t currentLiveCell = 0;
		for (int i = 0; i < columns; i++) {
			for (int j = 0; j < rows; j++) {
				bool currentCellState = cell[i][j].currentState;
				if (currentCellState == true)
				{
					int movex = i + ofRandom(-2, 2);
					int movey = j + ofRandom(-2, 2);
					cell[movex][movey].nextState = true;
					//cell[i][j].currentState = false;
					cell[i][j].nextState = false;
				}

				/*
				cell[i][j].activeNeighbors = getActiveNeighbors(i, j);
				
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
				}*/

			}
		}
		double p = double(currentLiveCell) / (double(columns) * double(rows));
		std::cout << p << "\n";
		plot->update(p);
		makeNextStateCurrent();
	}
}

int Matrix::lastCellState(int column, int row)
{
	return (column >= 0 && row >= 0 &&
		column < columns&& row < rows&&
		cell[column][row].lastState == true);
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
			cell[i][j].lastState = cell[i][j].currentState;
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
			if (cell[i][j].lastState == true) {
				ofSetColor(ofColor::blue);
				ofFill();
				ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
				ofNoFill();
			}
			if (cell[i][j].currentState == true) {
				ofSetColor(ofColor::green);
				ofFill();
				ofRect(i * cellWidth, j * cellHeight, cellWidth, cellHeight);
				ofNoFill();
			}
		}
	}
	plot->draw(1024, 10, 840, 640);
	gui.draw();
}

void Matrix::mousePressed(int x, int y, int button)
{
	int xcell = x / cellWidth;
	int ycell = y / cellHeight;
	if (xcell < columns && ycell < rows)
	{
		cell[xcell][ycell].currentState = !cell[xcell][ycell].currentState;
	}
}
