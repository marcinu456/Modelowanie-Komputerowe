#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);

	for (int i = 0; i < 239; i++) { this->particles.push_back(Particle()); }
}
//--------------------------------------------------------------
void ofApp::update() {

	for (Particle& particle : particles) { particle.Update(); }
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (Particle& particle : particles) { particle.Draw(); }
}
