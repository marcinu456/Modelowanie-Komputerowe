#include "Wolf.h"

Wolf::Wolf(ofVec2f _position, size_t _hp) :
	Agent(_position, _hp)
{
}

void Wolf::draw(ofColor color)
{
	ofSetColor(color);
	/*yourModel.setPosition(position.x, position.y, 0);
	yourModel.setRotation(0, 90, 90, 0, 00);
	double f = 0.1;
	yourModel.setScale(f, f, f);
	yourModel.drawFaces();*/
	ofDrawRectangle(position, 20, 20);
}
