#include "ofApp.h"

#include <vector>
#include <fstream>
#include <string>

ofApp::ofApp() :
	COUNT(1000),
	INFECTED_COUNT(1),
	SIZE(15.0),
	VELOCITY(2.5),
	PROB(0.075),
	RECOVERY_TIME(15),

	population()
{

	for(int i = 0; i < COUNT; i++) {
		Agent agent(ofVec2f(ofRandom(SIZE, 1000 - SIZE), ofRandom(SIZE, 1000 - SIZE)), VELOCITY, susceptible);

		population.push_back(agent);
	}

	for (int i = 0; i < INFECTED_COUNT; i++) {
		int rand = ofRandom(population.size());
		if (population[i].state != infected)
		{
			population[i].state = infected;
			population[i].recoveryTime = RECOVERY_TIME;
		}
	}
}

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){
	static constexpr bool REINFECT = 1;
	static constexpr bool SAVE_TO_FILE = 1;

	population.reserve(COUNT);
	for (int i = 0; i < COUNT; i++) {
		Agent& agent = population[i];
		agent.position += agent.velocity;
		if (agent.position.x < SIZE || agent.position.x > 1000 - SIZE){
			agent.velocity.x = -agent.velocity.x;
		}
		if (agent.position.y < SIZE || agent.position.y > 1000 - SIZE){
			agent.velocity.y = -agent.velocity.y;
		}

		if (agent.recoveryTime > 0) {
			agent.recoveryTime--;
		}
		else if (agent.recoveryTime == 0) {
			agent.state = recovered;
			agent.recoveryTime--;
		}

		for (int j = i+1; j < COUNT; j++) {
			if constexpr (REINFECT) {
				Agent& pedestrian = population[j];
				if (pedestrian.state == susceptible && agent.state == infected && (agent.position - pedestrian.position).length() < SIZE * 2 && ofRandom(1.0) < PROB) {
					pedestrian.state = infected;
					pedestrian.recoveryTime = RECOVERY_TIME;
				}
				else if (pedestrian.state == recovered && agent.state == infected && (agent.position - pedestrian.position).length() < SIZE * 2 && ofRandom(1.0) < PROB / 2) {
					pedestrian.state = infected;
					pedestrian.recoveryTime = RECOVERY_TIME;
				}
				else if(agent.state == susceptible && pedestrian.state == infected && (agent.position - pedestrian.position).length() < SIZE * 2 && ofRandom(1.0) < PROB) {
					agent.state = infected;
					agent.recoveryTime = RECOVERY_TIME;
				}
				else if(agent.state == recovered && pedestrian.state == infected && (agent.position - pedestrian.position).length() < SIZE * 2 && ofRandom(1.0) < PROB/2) {
					agent.state = infected;
					agent.recoveryTime = RECOVERY_TIME;
				}
			}
			else {
				Agent& pedestrian = population[j];
				if (pedestrian.state == susceptible && agent.state == infected && (agent.position - pedestrian.position).length() < SIZE * 2 && ofRandom(1.0) < PROB) {
					pedestrian.state = infected;
					pedestrian.recoveryTime = RECOVERY_TIME;
				}
				else if (agent.state == susceptible && pedestrian.state == infected && (agent.position - pedestrian.position).length() < SIZE * 2 && ofRandom(1.0) < PROB) {
					agent.state = infected;
					agent.recoveryTime = RECOVERY_TIME;
				}
			}
		}
	}
	if constexpr (SAVE_TO_FILE) {
		static std::ofstream ofs((std::string("../data/simulations" + std::to_string(REINFECT) + "/sim_") + std::to_string(PROB) + ".txt").c_str());
		size_t susCount = 0;
		size_t infCount = 0;
		size_t recCount = 0;
		for (int i = 0; i < COUNT; i++) {
			Agent& agent = population[i];
			switch (agent.state) {
			case susceptible:
				susCount++;
				break;
			case infected:
				infCount++;
				break;
			case recovered:
				recCount++;
				break;
			}
			ofDrawCircle(agent.position, SIZE);
		}
		ofs << susCount << " " << infCount << " " << recCount << "\n";
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < COUNT; i++) {
		Agent& agent = population[i];
		switch(agent.state){
		case susceptible:
			ofSetColor(126, 126, 126);
			break;
		case infected:
			ofSetColor(180, 100, 100);
			break;
		case recovered:
			ofSetColor(100, 180, 100);
			break;
		}
		ofDrawCircle(agent.position, SIZE);
	}
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
