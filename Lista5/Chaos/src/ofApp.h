#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "ofMain.h"
#include "Pendulum.h"

class ofApp : public ofBaseApp {

	std::vector<Pendulum> pendulum;
	size_t numberOfPendulus = 1000;
	std::vector<glm::vec4> states;
	std::ofstream ofs_energy;
	std::ofstream ofs_positions;
	std::ofstream ofs_phases;
	size_t iter = 0;


public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	~ofApp();
};
