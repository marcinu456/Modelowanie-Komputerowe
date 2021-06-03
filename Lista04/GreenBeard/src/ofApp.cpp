#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	for (int i = 0; i < countOfPopulation; i++) {
		ofVec2f test;
		double alpha = dist(gen) * 2 * M_PI;
		test.x = cos(alpha) * (1000 / 2 - 1) + 1000 / 2;
		test.y = sin(alpha) * (1000 / 2 - 1) + 1000 / 2;
		//test.x = cos(alpha) * (ofRandom(PeopleSize, 1000 - PeopleSize) / 2 - 1) + 1000 / 2; inside
		//test.y = sin(alpha) * (ofRandom(PeopleSize, 1000 - PeopleSize) / 2 - 1) + 1000 / 2; inside
		Agent agent(ofVec2f(test.x, test.y));
		population.push_back(agent);
	}
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < countOfPopulation; i++) {
		Agent& agent = population[i];
		ofDrawCircle(agent.position, PeopleSize);
	}
	ofVec2f test;
	test.x = 500;
	test.y = 500;
	ofNoFill();
	ofDrawCircle(test, 500);
	ofFill();
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
