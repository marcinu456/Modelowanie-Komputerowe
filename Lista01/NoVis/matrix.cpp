#include "matrix.h" 


Matrix::Matrix(int _rows, int _columns) :
	rows(_rows), columns(_columns)
{
	cell = new Cell * [columns];
	for (int i = 0; i < columns; i++) {
		cell[i] = new Cell[rows];
		for (int j = 0; j < rows; j++) {
			cell[i][j].currentState = false;
			cell[i][j].nextState = false;
		}
	}

	liveCellVector.resize(100);

	std::ofstream myfile;
	myfile.open("example.txt");
	myfile.close();
}
void Matrix::clear()
{
	howMany++;
	std::cout << howMany << " clear\n";
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			cell[i][j].currentState = false;
			cell[i][j].nextState = false;
		}
	}
}

void Matrix::randomGrid()
{
	std::random_device rd{};
	std::mt19937 engine{ rd() };
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	size_t currentLiveCell = 0;
	liveTime = 0;
	clear();
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++) {
			if (dis(rd) < 0.6) {
				cell[i][j].currentState = !cell[i][j].currentState;
				currentLiveCell++;
			}
		}
	}

}

void Matrix::update(bool active, size_t index) {
	//std::cout << "start\n";
	while (active && liveTime < timeIndex) {

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
		liveTime++;
		liveCellVector[index].push_back(currentLiveCell);
		makeNextStateCurrent();
	}
	//std::cout << "end\n";
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
		column < columns&& row < rows&&
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
	
	std::ofstream myfile;
	myfile.open("example.txt", std::ios::app);

	for (size_t i = 0; i < timeIndex; i++)
	{
		myfile << i; 
		for (size_t j = 0; j < liveCellVector.size(); j++)
		{
			myfile << "	" << liveCellVector[j][i];
		}
		myfile << "\n";
	}
	myfile.close();




}
