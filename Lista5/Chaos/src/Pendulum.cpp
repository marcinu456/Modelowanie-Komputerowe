#include "Pendulum.h"

Pendulum::Pendulum(double px, double py, double theta0, double length0, double mass0, double theta1, double length1, double mass1):
	px(px),py(py),theta0(theta0),length0(length0),mass0(mass0), theta1(theta1), length1(length1), mass1(mass1)
{
	points.resize(100);
}

void Pendulum::setColors(ofColor _color0, ofColor _color1, ofColor _color2)
{
	color0 = _color0;
	color1 = _color1;
	color2 = _color2;
}

void Pendulum::computeAnglesEuler(double dt)
{
	/*theta0bis = -g * (2 * mass0 + mass1) * std::sin(theta0) - mass1 * g * std::sin(theta0 - 2 * theta1) - 2 * std::sin(theta0 - theta1) * mass1 *
		(theta1prim * theta1prim * length1 + theta0prim * theta0prim * length0 * std::cos(theta0 - theta1));
	theta0bis /= length0 * (2 * mass0 * mass1 - mass1 * std::cos(2 * theta0 - 2 * theta1));

	theta1bis = 2 * std::sin(theta0 - theta1) * (theta0prim * theta0prim * length0 * (mass0 + mass1) + g * (mass0 + mass1) * std::cos(theta0) +
		theta1prim * theta1prim * length1 * mass1 * std::cos(theta0 - theta1));
	theta1bis /= length1 * (2 * mass0 + mass1 - mass1 * std::cos(2 * theta0 - 2 * theta1));*/

	//source http://www.team.kdm.p.lodz.pl/master/Jankowski.pdf
	double u = 1 + mass0 + mass1;
	theta0bis =
		(g * (sin(theta1) * cos(theta0 - theta1) - u * sin(theta0))
			- (length1 * pow(theta1prim, 2) + length0 * pow(theta0prim, 2) * cos(theta0 - theta1)) * sin(theta0 - theta1))
		/ (length0 * (u - pow(cos(theta0 - theta1), 2)));
	theta1bis =
		(g * u * (sin(theta0) * cos(theta0 - theta1) - sin(theta1)) + (u * length0 * pow(theta0prim, 2)
			+ length1 * pow(theta1prim, 2) * cos(theta0 - theta1)) * sin(theta0 - theta1))
		/ (length1 * (u - pow(cos(theta0 - theta1), 2)));


	theta0prim = theta0prim + theta0bis * dt;
	theta1prim = theta1prim + theta1bis * dt;

	theta0 = theta0 + theta0prim * dt;
	theta1 = theta1 + theta1prim * dt;
}

void Pendulum::computeAnglesRunge(double dt)
{
	//source https://www.myphysicslab.com/pendulum/double-pendulum-en.html
	theta0bis = -g * (2 * mass0 + mass1) * sin(theta0) - mass1 * g * sin(theta0 - (2 * theta1)) - 2 * (sin(theta0 - theta1)) * mass0 * ((theta1prim * theta1prim) * length1 + (theta0prim * theta0prim) * length0 * cos(theta0 - theta1));

	theta0bis /= length0 * (2 * mass0 + mass1 - mass1 * cos(2 * theta0 - 2 * theta0));

	theta1bis = 2 * sin(theta0 - theta1) * ((theta0prim * theta0prim) * length0 * (mass0 + mass1) + g * (mass0 + mass1) * cos(theta0) + (theta1prim * theta1prim) * length1 * mass1 * cos(theta0 - theta1));

	theta1bis /= length1 * (2 * mass0 + mass1 - mass1 * cos(2 * theta0 - 2 * theta1));

	theta0prim = theta0prim + theta0bis * dt;
	theta1prim = theta1prim + theta1bis * dt;

	theta0 = theta0 + theta0prim * dt;
	theta1 = theta1 + theta1prim * dt;
}

void Pendulum::computePosition()
{
	x0 = px + length0 * std::sin(theta0);
	y0 = py + length0 * std::cos(theta0);

	x1 = x0 + length1 * std::sin(theta1);
	y1 = y0 + length1 * std::cos(theta1);
}

void Pendulum::drawLines()
{
	ofSetColor(color0);
	//ofSetColor(ofColor::brown);
	ofDrawLine(px, py, x0, y0);

	ofSetColor(color1);
	//ofSetColor(ofColor::white);
	ofDrawLine(x0, y0, x1, y1);
}

void Pendulum::trails()
{

	ofSetColor(color2);

	ofVec2f tmp;
	tmp.x = x1;
	tmp.y = y1;
	
	points[itera % 100] = tmp;
	//points.push_back(tmp);

	for (int i = 0; i < points.size(); i++) {
		point = points[i];
		ofDrawCircle(point.x, point.y, 1, 1);
	}
	itera++;
}

void Pendulum::air()
{
	theta0prim *= 0.993;
	theta1prim *= 0.993;
}

glm::vec4 Pendulum::getState() {
	return glm::vec4(theta0, theta0prim, theta1, theta1prim);
}


std::stringstream Pendulum::streamEnergy() {
	double ek = mass0 * pow(theta0prim * length0, 2) / 2 + mass1 * pow(theta1prim * length1, 2) / 2;
	double ep = mass0 * g * (-y0 + (px + length0)) + mass1 * g * (-y1 + (px + length1));

	return std::stringstream() << ek << " " << ep << " " << ek + ep;
}

std::stringstream Pendulum::streamPosition() {
	return std::stringstream() << x1 << " " << 800 - y1;
}
std::stringstream Pendulum::streamPhase() {
	return std::stringstream() << theta0 << " " << theta0prim << " " << theta1 << " " << theta1prim;
}