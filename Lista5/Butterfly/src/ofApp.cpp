#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	for (size_t i = 0; i < numberOfButterfly; i++)
	{
		butterfly.push_back(Butterfly(ofPoint(400+i*15,400,400)));
		butterfly[i].setColor(ofColor::brown);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	iter++;
	

	for (size_t i = 0; i < numberOfButterfly; i++)
	{
		ofColor tmp(iter % 255, (125+i*50)%255, 125);
		butterfly[i].setColor(tmp);
		butterfly[i].computePosition(.005);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
	ofEnableDepthTest();
	for (size_t i = 0; i < numberOfButterfly; i++)
	{
		butterfly[i].trails();
	}
	ofDrawSphere(ofPoint(400, 400, 400), 1);
	ofDisableDepthTest();
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
