#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	active = false;
	cols = 100;
	rows = 100;

	cellWidth = ofGetWidth() / cols;
	cellHeight = ofGetHeight() / cols;
	matrix = new Matrix(cols, rows);


	ofBackground(ofColor::gray);
	ofSetVerticalSync(false);
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
			active = false;
			break;
		case '1':
			matrix->randomGrid(0.1);
			break;
		case '2':
			matrix->randomGrid(0.3);
			break;
		case '3':
			matrix->randomGrid(0.6);
			break;
		case '4':
			matrix->randomGrid(0.75);
			break;
		case '5':
			matrix->randomGrid(0.8);
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
	matrix->mousePressed(x, y, button);
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
