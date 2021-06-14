#pragma once

#include "ofMain.h"
#include "Plant.h"
#include "Rabbit.h"
#include "Wolf.h"

#include <vector>
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp {
	ofEasyCam cam;
	ofxAssimpModelLoader yourModel;

	const double SIZE = 10;

	const size_t PLANT_COUNT = 8;
	const size_t PLANT_MAX_HP = 240;
	const size_t PLANT_REPRODUCE_TIME = 30;
	const size_t PLANT_REPRODUCE_COUNT = 8;

	const size_t RABBIT_COUNT = 8;
	const size_t RABBIT_MAX_HP = 300;
	const size_t RABBIT_MAX_HUNGRY_HP_LEVEL = 150;
	const double RABBIT_VELOCITY = 2.5;
	const double RABBIT_REPRODUCE_COUNT = 4;

	const size_t WOLF_COUNT = 4;
	const size_t WOLF_MAX_HP = 500;
	const size_t WOLF_MAX_HUNGRY_HP_LEVEL = 150;
	const double WOLF_VELOCITY = 2;
	const double WOLF_REPRODUCE_COUNT = 1;


	std::vector<Plant> plants;
	std::vector<Rabbit> rabbits;
	std::vector<Wolf> wolfes;

	size_t iter = 0;
	std::ofstream ofs;
	public:
		~ofApp();

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
