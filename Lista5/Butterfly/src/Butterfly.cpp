#include "Butterfly.h"

Butterfly::Butterfly(ofPoint _point) :
	point(_point)
{
	color0.resize(number);
	points.resize(number);
}

void Butterfly::setColor(ofColor _color0)
{
	color0[itera% number] = _color0;
}

void Butterfly::computePosition(double dt)
{
	point.x = point.x + 10.0 * (point.y - point.x) * dt;
	point.y = point.y + (-point.x * point.z + 28.0 * point.x - point.y) * dt;
	point.z = point.z + (point.x * point.y - (8.0 / 3.0) * point.z) * dt;
}



void Butterfly::trails()
{

	

	points[itera % number] = point;
	//points.push_back(point);

	for (int i = 0; i < points.size(); i++) {
		ofSetColor(color0[i]);
		ofDrawSphere(points[i], .25);
	}
	itera++;
}
