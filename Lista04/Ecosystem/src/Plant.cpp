#include "Plant.h"

Plant::Plant(ofVec2f _position, size_t _hp) :
	Agent(_position, _hp)
{

}

void Plant::draw(ofColor color)
{
	ofSetColor(color);
	/*yourModel.setPosition(position.x, position.y, 0);
	yourModel.setRotation(0, 90, 90, 0, 00);
	double f = 0.1;
	yourModel.setScale(f, f, f);
	yourModel.drawFaces();*/
	ofDrawTriangle(position, ofVec2f(position.x + 20, position.y), ofVec2f(position.x + 10, position.y+20));
}
