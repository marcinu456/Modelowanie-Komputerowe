#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	for (size_t i = 0; i < numberOfButterfly; i++)
	{
		butterfly.push_back(Butterfly(ofPoint(400,400,400)));
		butterfly[i].setColor(ofColor::brown);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	iter++;
	ofColor tmp(iter%155, iter*3%250,iter*4%120);

	for (size_t i = 0; i < numberOfButterfly; i++)
	{
		butterfly[i].setColor(tmp);
		butterfly[i].computePosition(.005);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	for (size_t i = 0; i < numberOfButterfly; i++)
	{
		butterfly[i].trails();
	}
	ofDrawSphere(ofPoint(400, 400, 400), 1);
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
