#pragma once

#include "ofMain.h"
#include <vector>
#include "agent.h"
#include "ofxGraph.h"

class ofApp : public ofBaseApp{
	const size_t countOfPopulation;
	const size_t countOfInvected;
	const int IllTime;
	const float PeopleSize;
	const float VELOCITY;
	const double IllProbolity;
	bool Reinfected = 1;
	size_t iter = 0;
	size_t totalIter = 300;
	std::ofstream ofs;

	std::vector<Agent> population;
	ofxGraph graph;
	public:
		ofApp();
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
