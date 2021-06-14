#include "Rabbit.h"
#include <cmath>


Rabbit::Rabbit(ofVec2f _position, size_t _hp) :
	Agent(_position, _hp)
{
}

void Rabbit::draw(ofColor color)
{
	ofSetColor(color);
	/*yourModel.setPosition(position.x, position.y, 0);
	yourModel.setRotation(0, 90, 90, 0, 00);
	double f = 0.1;
	yourModel.setScale(f, f, f);
	yourModel.drawFaces();*/
	ofDrawCircle(position, 10);
}

