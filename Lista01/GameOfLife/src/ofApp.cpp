#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	active = false;
	cols = 100;
	rows = 100;

	cellWidth = ofGetWidth() / cols;
	cellHeight = ofGetHeight() / cols;
	matrix = new Matrix(cols, rows);


	ofBackground(ofColor::white);
	ofSetFrameRate(60);
}


//--------------------------------------------------------------
void ofApp::update(){
	matrix->update(active);
}




//--------------------------------------------------------------
void ofApp::draw(){
	matrix->draw();
}







//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
		case ' ':
			active = !active;
			break;
		case 'r':
			matrix->clear();
			break;
		case 'f':
			matrix->randomGrid();
			break;
		default:
			break;
	}
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
void ofApp::mousePressed(int x, int y, int button) {
	int xcell = x / cellWidth;
	int ycell = y / cellHeight;
	if (xcell < cols && ycell < rows)
	{
		matrix->cell[xcell][ycell].currentState = !matrix->cell[xcell][ycell].currentState;
	}
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
