#pragma once
#include <ofMain.h>
#include <sstream>

class Butterfly {
private:
	vector<ofPoint> points;
	ofPoint point;
	size_t itera = 0;
	vector <ofColor> color0;
	size_t number = 1000;
public:
	Butterfly(ofPoint _point);

	void setColor(ofColor _color);
	void computePosition(double dt);
	void trails();
};