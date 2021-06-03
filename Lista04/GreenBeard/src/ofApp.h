#pragma once

#include "ofMain.h"
#include "House.h"
#include "Agent.h"
#include "Tree.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <random>
#include <climits>
#include <cmath>
#include <math.h>
#include <string>
#include <stdint.h>
# define M_PI           3.14159265358979323846  /* pi */
class ofApp : public ofBaseApp{

	std::vector<House> houses;
	std::vector<Tree> trees;
	size_t countOfPopulation = 0;
	size_t countOfHouse = 80;
	size_t countOfTrees = 1000;
	size_t houseSize = 50;
	size_t treeSize = 30;
	size_t numberOfPredators = 80;
	ofEasyCam camera;

	std::ofstream ofs;

	size_t iter = 0;
	size_t totalIter = 300;
	public:
		void setup();
		void update();
		void draw();

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
