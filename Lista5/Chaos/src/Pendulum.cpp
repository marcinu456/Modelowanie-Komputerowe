#include "Pendulum.h"

Pendulum::Pendulum(double px, double py, double theta0, double length0, double mass0, double theta1, double length1, double mass1):
	px(px),py(py),theta0(theta0),length0(length0),mass0(mass0), theta1(theta1), length1(length1), mass1(mass1)
{
}

void Pendulum::computetions(double dt)
{

	theta0 = theta0 + theta0prim * dt;
	theta1 = theta1 + theta1prim * dt;


	theta0bis = -g * (2 * mass0 + mass1) * std::sin(theta0) - mass1 * g * std::sin(theta0 - 2 * theta1) - 2 * std::sin(theta0 - theta1) * mass1 *
		(theta1prim * theta1prim * length1 + theta0prim * theta0prim * length0 * std::cos(theta0 - theta1));
	theta0bis /= length0 * (2 * mass0 * mass1 - mass1 * std::cos(2 * theta0 - 2 * theta1));

	theta1bis = 2 * std::sin(theta0 - theta1) * (theta0prim * theta0prim * length0 * (mass0 + mass1) + g * (mass0 + mass1) * std::cos(theta0) +
		theta1prim * theta1prim * length1 * mass1 * std::cos(theta0 - theta1));
	theta1bis /= length1 * (2 * mass0 + mass1 - mass1 * std::cos(2 * theta0 - 2 * theta1));

	theta0prim = theta0prim + theta0bis * dt;
	theta1prim = theta1prim + theta1bis * dt;

	x0 = px + length0 * std::sin(theta0);
	y0 = py + length0 * std::cos(theta0);

	x1 = x0 + length1 * std::sin(theta1);
	y1 = y0 + length1 * std::cos(theta1);
}

void Pendulum::drawLines()
{
	//ofSetColor(c0, 255);
	ofSetColor(ofColor::brown);
	ofDrawLine(px, py, x0, y0);

	//ofSetColor(c1, 255);
	ofSetColor(ofColor::white);
	ofDrawLine(x0, y0, x1, y1);
}
