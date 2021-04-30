#include "Particle.h"

Particle::Particle() {

	int x = (int)(ofRandom(ofGetWidth()) / 20) * 20;
	int y = (int)(ofRandom(ofGetHeight()) / 20) * 20;
	this->location = ofPoint(x, y);

	this->directions[0] = ofPoint(1, 0);
	this->directions[1] = ofPoint(-1, 0);
	this->directions[2] = ofPoint(0, 1);
	this->directions[3] = ofPoint(0, -1);
}

Particle::~Particle() {

}

void Particle::Update() {

	if (ofGetFrameNum() % 5 == 0) {
		location.x += ofRandom(-1, 1);
		location.y += ofRandom(-1, 1);
		/*int r = ofRandom(4);
		this->direction = this->directions[r];

		if (this->location.x < 0) { this->direction = ofPoint(1, 0); }
		else if (this->location.x > ofGetWidth()) { this->direction = ofPoint(-1, 0); }

		if (this->location.y < 0) { this->direction = ofPoint(0, 1); }
		else if (this->location.y > ofGetHeight()) { this->direction = ofPoint(0, -1); }*/
	}

	this->location += this->direction * 2;
	this->logs.push_front(location);
	while (this->logs.size() > 90) { this->logs.pop_back(); }
}

void Particle::Draw() {

	ofFill();
	ofDrawCircle(this->location, 3);

	ofNoFill();
	/*ofBeginShape();
	for (ofPoint& log : this->logs) {

		ofVertex(log);
	}
	ofEndShape();*/
}