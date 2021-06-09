#pragma once
#include <ofMain.h>
#include <sstream>

class Pendulum {
private:
	double px=0;
	double py=0;

	double x0=0;
	double y0=0;
	double theta0prim=0;
	double theta0bis=0;
	double theta0=0;
	double length0=0;
	double mass0=0;
	ofColor c0;

	double x1=0;
	double y1=0;
	double theta1prim=0.0;
	double theta1bis=0;
	double theta1=0;
	double length1=0;
	double mass1=0;
	ofColor c1;

	double g = 0.9;

public:
	Pendulum(double px, double py, double theta0, double length0, double mass0, double theta1, double length1, double mass1);

	void setColors(ofColor _color0, ofColor _color1);
	void setColor(ofColor _color);
	void computeAnglesEuler(double dt);
	void computeAnglesRunge(double dt);
	void computePosition();

	void drawLines();


	glm::vec4 getState();
	std::stringstream streamEnergy();
	std::stringstream streamPosition();
	std::stringstream streamPhase();

};