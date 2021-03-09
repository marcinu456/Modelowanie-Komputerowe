#pragma once

#include <vector>
#include "ofMain.h"
#include "cell.h"
#include "matrix.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();

		int getActiveNeighbors(int column, int row);
		int currentCellState(int column, int row);

		void makeNextStateCurrent();

		void randomGrid();

		void draw();
		void clear();

		Matrix matrix;
		int rows, cols;
		float cellWidth, cellHeight;
		int sizeOfCell;
		bool active;



		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
