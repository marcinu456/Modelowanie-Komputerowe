#pragma once

#include "ofMain.h"
#include "Butterfly.h"
class ofApp : public ofBaseApp{

	std::vector<Butterfly> butterfly;
	size_t numberOfButterfly = 4;
	ofEasyCam cam;
	size_t iter = 0;
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
